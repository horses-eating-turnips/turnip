// $Id: mollom.js,v 1.2.2.5 2009/04/12 19:29:20 dries Exp $

Drupal.behaviors.mollom = function() {
  // Add onclick.event handlers for CAPTCHA links:
  $('a#mollom-audio-captcha').click(getAudioCaptcha);
  $('a#mollom-image-captcha').click(getImageCaptcha);
}

function getAudioCaptcha() {
  // Extract the Mollom session ID from the form:
  var mollomSessionId = $("input#edit-mollom-session-id").val();

  // Retrieve an audio CAPTCHA:
  var data = $.get(Drupal.settings.basePath + 'mollom/captcha/audio/' + mollomSessionId,
    function(data) {
     // When data is successfully loaded, replace
     // contents of captcha-div with an audio CAPTCHA:
     $('a#mollom-captcha').parent().html(data);

     // Add an onclick-event handler for the new link:
     $('a#mollom-image-captcha').click(getImageCaptcha);
   });
   return false;
}

function getImageCaptcha() {
  // Extract the Mollom session ID from the form:
  var mollomSessionId = $('input#edit-mollom-session-id').val();

  // Retrieve an image CAPTCHA:
  var data = $.get(Drupal.settings.basePath + 'mollom/captcha/image/' + mollomSessionId,
    function(data) {
     // When data is successfully loaded, replace
     // contents of captcha-div with an image CAPTCHA:
     $('a#mollom-captcha').parent().html(data);

     // Add an onclick-event handler for the new link:
     $('a#mollom-audio-captcha').click(getAudioCaptcha);
   });
   return false;
}
