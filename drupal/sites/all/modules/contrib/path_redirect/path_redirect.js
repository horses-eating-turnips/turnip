// $Id: path_redirect.js,v 1.1.2.2 2009/12/02 01:47:30 davereid Exp $

Drupal.verticalTabs = Drupal.verticalTabs || {};

Drupal.verticalTabs.path_redirect = function() {
  if ($('fieldset.vertical-tabs-path_redirect table tbody td.empty').size()) {
    return Drupal.t('No redirects');
  }
  else {
    var redirects = $('fieldset.vertical-tabs-path_redirect table tbody tr').size();
    return Drupal.formatPlural(redirects, '1 redirect', '@count redirects');
  }
}
