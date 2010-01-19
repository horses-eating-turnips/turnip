// $Id: theme.js 881 2009-09-04 00:11:44Z jhedstrom $

Drupal.behaviors.admin_theme = function(context) {
  // Toggle help
  $('a.help-toggle:not(.processed)').each(function() {
    $(this).addClass('processed').click(function() {
      $(this).toggleClass('help-expanded');
      $('#help').toggle();
      return false;
    });
  });

  // Toggle help
  $('a.subnav-toggle:not(.processed)').each(function() {
    $(this).addClass('processed').click(function() {
      $(this).toggleClass('subnav-expanded');
      $('#secondary-links').toggle();
      return false;
    });
  });

  // Fieldset
  $('div.fieldset:not(.admin-processed)').each(function () {
    var $fieldset = $(this);
    $fieldset.addClass('admin-processed');
    if ($fieldset.is('.collapsible')) {
      if ($('.error', $fieldset).length > 0) {
        $fieldset.removeClass('collapsed');
      }
      if ($fieldset.is('.collapsed')) {
        $fieldset.children('.fieldset-content').hide();
      }
      $fieldset.children('.fieldset-title').click(function () {
        var $title = $(this);
        if ($fieldset.is('.collapsed')) {
          $title.next('.fieldset-content').slideDown('fast');
          $fieldset.removeClass('collapsed');
        }
        else {
          $title.next('.fieldset-content').slideUp('fast');
          $fieldset.addClass('collapsed');
        }
        return false;
      });
    }
  });
}
