// $Id: path_redirect.vertical_tabs.node_form.js 900 2010-01-18 23:01:52Z jhedstrom $

Drupal.verticalTabs = Drupal.verticalTabs || {};

Drupal.verticalTabs.path_redirect = function() {
  if ($('table.path-redirects tbody td.path-redirect-none').size()) {
    return Drupal.t('No redirects');
  }
  else {
    var redirects = $('table.path-redirects tbody tr').size();
    return Drupal.formatPlural(redirects, '1 redirect', '@count redirects');
  }
}
