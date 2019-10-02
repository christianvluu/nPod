"use strict"

// Global configuration parameters
var config			= Object.assign( {}, require('../../config/config.json') );

// Global helper functions
var reportError		= require('../../app/helpers/messages.js').reportError;
var minimal			= require('../../app/models/dbProfiles.js').minimal;

// Database access functions
var dbProfiles		= require('../../app/models/dbProfiles.js');
var request = require('request');


// MAIN MODULE DEFINITION
module.exports = function ( io ) {
var nPod = {};


//
nPod.confirm = function( req, res, next ) {
	var userInfo = req.session.userInfo;
	return next();


	if ( userInfo.userID !== Number( req.params.userID ) ) {
		res.send( "USER MISMATCH" );
	} else {
		next();
	}
}

// login parameters for thinger.io
nPod.loginParams = require('../config/password_nPod.js').loginParams;

//
nPod.viewNPodPage = function( req, res, next ) {
	var error = { location: "survey.nPod.viewNPodPage" };
	var dataObj = Object.assign( {}, req.session );
	dataObj.config = config;

	// retrieve access token from thinger.io and store in access_token
	var access_token = "";
	request.post(
		{url: "https://api.thinger.io/oauth/token", form: nPod.loginParams},
		(err,httpResponse,body) => {
			nPod.access_token = JSON.parse( body ).access_token;
		} );
	res.status(201).render( 'pages/nPod', dataObj );
}

//
nPod.getData = function( req, res, next ) {
	var url = "https://api.thinger.io/v1/users/npod/devices";
		url += "/" + req.query.device + "/" + req.query.resource;
	request.get(
		url, {qs: { 'authorization': nPod.access_token } },
		(err,httpResponse,body) => {
			res.send( body );
		} );
}

//
nPod.postData = function( req, res, next ) {
	res.send( "DATA received" );
}


return nPod;
};
