<?php
// $Id: mollom.inc 887 2009-09-24 15:51:14Z jhedstrom $

/**
 * @file
 * Miscellaneous functions for the mollom module.
 */

/**
 * This function generates an array with all information required to
 * authenticate against Mollom.  To prevent forged requests where you are
 * impersonated, each request is signed with a hash based on a private
 * key and a timestamp.
 *
 * Both the client and the server share the secret key used to create
 * the authentication hash.  They both hash a timestamp with the secret
 * key, and if the hashes match, the authenticity of the message is
 * validated.
 *
 * To avoid someone intercepting a (hash, timestamp)-pair and using it
 * to impersonate a client, Mollom reject any request where the timestamp
 * is more than 15 minutes off.
 *
 * Make sure your server's time is synchronized with the world clocks,
 * and that you don't share your private key with anyone else.
 */
function _mollom_authentication() {

  $public_key = variable_get('mollom_public_key', '');
  $private_key = variable_get('mollom_private_key', '');

  // Generate a timestamp according to the dateTime format (http://www.w3.org/TR/xmlschema-2/#dateTime):
  $time = gmdate("Y-m-d\TH:i:s.\\0\\0\\0O", time());

  // Generate a random number:
  $nonce = md5(mt_rand());

  // Calculate a HMAC-SHA1 according to RFC2104 (http://www.ietf.org/rfc/rfc2104.txt):
  $hash = base64_encode(
    pack('H*', sha1((str_pad($private_key, 64, chr(0x00)) ^ (str_repeat(chr(0x5c), 64))) .
    pack('H*', sha1((str_pad($private_key, 64, chr(0x00)) ^ (str_repeat(chr(0x36), 64))) .
    $time .':'. $nonce .':'. $private_key))))
  );

  // Store everything in an array.  Elsewhere in the code, we'll add the
  // actual data before we pass it onto the XML-RPC library:
  $data['public_key'] = $public_key;
  $data['time'] = $time;
  $data['hash'] = $hash;
  $data['nonce'] = $nonce;

  return $data;
}

/**
 * This function refreshes the list of servers that can be used to contact Mollom.
 */
function _mollom_retrieve_server_list() {
  // Start from a hard coded list of servers:
  $servers = array('http://xmlrpc1.mollom.com', 'http://xmlrpc2.mollom.com', 'http://xmlrpc3.mollom.com');

  // Use the list of servers to retrieve a list of servers from mollom.com:
  foreach ($servers as $server) {
    $result = xmlrpc($server .'/'. MOLLOM_API_VERSION, 'mollom.getServerList', _mollom_authentication());
    if (!xmlrpc_error()) {
      return $result;
    }
    else {
      watchdog('mollom', 'Error @errno: %server - %message - mollom.getServerList', array('@errno' => xmlrpc_errno(), '%server' => $server, '%message' => xmlrpc_error_msg()), WATCHDOG_ERROR);
    }
  }

  return array();
}
