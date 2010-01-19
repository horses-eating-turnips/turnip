// $Id: admin_toolbar.js 881 2009-09-04 00:11:44Z jhedstrom $

Drupal.admin = Drupal.admin || {};
Drupal.admin.toolbar = Drupal.admin.toolbar || {};

Drupal.admin.toolbar.setActive = function(toolbar_id) {
  // Show the right toolbar
  $('#admin-toolbar .depth-1 ul.links').addClass('collapsed');
  $(toolbar_id).removeClass('collapsed');
  $('div#admin-toolbar, div#admin-toolbar .depth-1').removeClass('collapsed');

  // Switch link active class to corresponding menu item
  var link_id = toolbar_id.replace('admin-toolbar', 'admin-link');
  $('#admin-toolbar .depth-0 ul.links a').removeClass('active');
  $(link_id).addClass('active');
}

Drupal.behaviors.admin_toolbar = function(context) {

  // Primary menus
  $('#admin-toolbar .depth-0 ul.links a:not(.processed)').each(function() {
    var target = $(this).attr('id');
    if (target) {
      target = '#'+ target.replace('admin-link', 'admin-toolbar');
      if ($(target, '#admin-toolbar').size() > 0) {
        // If this link is active show this toolbar on setup
        if ($(this).parent().is('.active-trail')) {
          Drupal.admin.toolbar.setActive(target);
        }
        // Add click handler
        $(this).click(function() {
          Drupal.admin.toolbar.setActive(target);
          return false;
        });
      }
    }
    $(this).addClass('processed');
  });

  $('#admin-toolbar .depth-1 span.close:not(.processed)').each(function() {
    $(this).click(function() {
      $('#admin-toolbar .depth-1').addClass('collapsed');
      return false;
    });
    $(this).addClass('processed');
  });

  // Secondary menus
  $('#admin-toolbar .depth-1 ul.links:not(.processed)').each(function() {
    $(this).addClass('processed');
  });
}
