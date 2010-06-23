// $Id: jquery.drilldown.js,v 1.1.2.5 2010/02/04 00:34:32 yhahn Exp $

/**
 * Generic menu drilldown plugin for standard Drupal menu tree markup.
 * The plugin should be inited against a DOM element that *contains*
 * a Drupal ul.menu tree. Example:
 * 
 *   $('div.block-menu').drilldown('init', params);
 * 
 * You must provide the following parameters as settings:
 * 
 *   var params = {
 *     activePath : A drupal menu path that is currently active including the basePath e.g. "/mysite/node"
 *     trail : A jquery selector to the DOM element that should act as the trail container, e.g. "div.my-menu-breadcrumb-trail"
 *   }
 *
 */
(function($) {
  $.fn.drilldown = function(method, settings) {
    var menu = this;
    var activePath;

    switch (method) {
      case 'goTo':
        // If the passed link refers to the current page, don't follow through
        // the link.
        if (this.activePath && this.activePath === $(settings.activeLink).attr('href')) {
          return false;
        }
        return true;
      case 'setActive':
        var breadcrumb = [];
        var activeMenu;

        $(settings.activeLink).each(function() {
          // Traverse backwards through menu parents and build breadcrumb array.
          $(this).parents('ul.menu').each(function() {
            $(this).siblings('a').each(function() {
              breadcrumb.unshift($(this));
            });
          });

          // If we have a child menu (actually a sibling in the DOM), use it
          // as the active menu. Otherwise treat our direct parent as the
          // active menu.
          if ($(this).next().is('ul.menu')) {
            activeMenu = $(this).next();
            breadcrumb.push($(this));
          }
          else {
            activeMenu = $(this).parents('ul.menu');
          }
          if (activeMenu) {
            $('.drilldown-active-trail', menu).removeClass('drilldown-active-trail');
            $('ul.menu', menu).removeClass('drilldown-active-menu').removeClass('clear-block');
            $(activeMenu[0]).parents('li').addClass('drilldown-active-trail');
            $(activeMenu[0]).addClass('drilldown-active-menu').addClass('clear-block').parents('li').show();
          }
        });

        // Render the breadcrumb to the target DOM object
        if (breadcrumb.length > 0) {
          var trail = $(settings.trail);
          trail.empty();
          for (var key in breadcrumb) {
            if (breadcrumb[key]) {
              // We don't use the $().clone() method here because of an
              // IE & jQuery 1.2 bug.
              // var clone = $(breadcrumb[key]).clone();
              var clone = $(breadcrumb[key]).get(0).cloneNode(true);
              $(clone)
                .unbind('click')
                .addClass('depth-'+key)
                .appendTo(trail);

              // We add a reference to the original link and a click handler
              // that traces back to that instance to set as the active link.
              $('a.depth-'+key, trail)
                .data('original', $(breadcrumb[key]))
                .click(function() {
                  settings.activeLink = $(this).data('original');
                  // If the clicked link does not reference the current
                  // active menu, set it to be active.
                  if (settings.activeLink.siblings('ul.drilldown-active-menu').size() === 0) {
                    menu.drilldown('setActive', settings);
                    return false;
                  }
                  // Otherwise, pass-through and allow the link to be clicked.
                  return menu.drilldown('goTo', settings);
                });
            }
          }
        }

        // Event in case others need to update themselves when a new active
        // link is set.
        $(menu).trigger('refresh.drilldown');
        break;
      case 'init':
        $(menu).addClass('drilldown');
        $(settings.trail).addClass('drilldown-trail');

        // Set initial active menu state.
        var activeLink;
        if (settings.activePath && $('ul.menu a[href='+settings.activePath+']', menu).size() > 0) {
          this.activePath = settings.activePath;
          activeLink = $('ul.menu a[href='+settings.activePath+']', menu).addClass('active');
        }
        if (!activeLink) {
          activeLink = $('ul.menu a.active', menu).size() ? $('ul.menu a.active', menu) : $('ul.menu > li > a', menu);
        }
        if (activeLink) {
          menu.drilldown('setActive', {'activeLink': $(activeLink[0]), 'trail': settings.trail});
        }

        // Attach click handlers to menu items
        $('ul.menu li:has(ul.menu)', this).click(function() {
          if ($(this).parent().is('.drilldown-active-menu')) {
            if (menu.data('disableMenu')) {
              return true;
            }
            else {
              var url = $(this).children('a').attr('href');
              var activeLink = $('ul.menu a[href='+url+']', menu);
              menu.drilldown('setActive', {'activeLink': activeLink, 'trail': settings.trail});
              return false;
            }
          }
        });
        $('ul.menu li:has(ul.menu) a', menu).click(function() {
          menu.data('disableMenu', true);
        });
        break;
    }
    return this;
  };
})(jQuery);
