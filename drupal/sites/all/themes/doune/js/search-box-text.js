/**
 * Autofills search box with 'Search this site' when empty
 * and clears 'Search this site' when focused
 */
Drupal.behaviors.searchFormText = function(context) {
  $('#search-box .form-text').val('').bind( 'load blur', function() {
    if( $(this).val() == '' ) {
      $(this).val(Drupal.t('Search this site'));
    }
  });
  $('#search-box .form-text').val('Search this site').focus( function() {
    if( $(this).val() == 'Search this site' ) {
      $(this).val('');
    }
  });
}
