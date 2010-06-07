// $Id: README.txt,v 1.1.2.2 2009/04/13 23:50:41 grendzy Exp $

INSTALLATION
------------

Copy securepages_prevent_hijack/ to your module directory and then enable on the admin modules page.

In order to prevent getting logged out the first time you enable it, make sure you are accessing admin/build/modules via SSL.  If you do get logged out at this point, don't panic, you can just log in again.  This should only happen once.

Also, other users' session will become invalid the first time you enable it.  On a busy site with a lot of logged in users, you should consider emptying the sessions table with the following SQL:
"truncate sessions".

It's *not* necessary to change your PHP cookie settings. [1]


DESCRIPTION
-----------

This module is intended to prevent hijacked sessions ( http://en.wikipedia.org/wiki/Session_hijacking ) from accessing SSL pages when used with securepages.

Strictly speaking, this does not *prevent* hijacking, since the session cookie itself.  Instead, hijacked sessions are detected, and blocked from accessing SSL pages.


INNER WORKINGS
--------------

Even if a username/password are transmitted to a site over SSL, the session is still subject to hijacking because the session cookie is passed in plaintext. One obvious solution is to require SSL for all requests but this has downsides. A valuable compromise is to prevent a hijacked session ID from being used to access an SSL-protected page; any pages that allow some kind of critical activity (buying products against a stored credit card number or whatever) can then require SSL and know the session ID was not hijacked.

This is accomplished by using a second session ID cookie with the 'secure' flag set so it is only transmitted to SSL-protected pages. Here's how it would work:

- When a user logs in, a token is generated via drupal_get_token(). In reply to the login submission (which was to an SSL-protected page), the secure token is sent to the user as a second cookie named SSL_SESSION_NAME with the 'secure' flag set.

- Whenever a request arrives via SSL, the session is loaded in the normal way (using the non-secure session ID) and then the token is tested with drupal_valid_token(). If it's not valid, the session has been hijacked and the request is refused.


CREDITS
-------

Original concept and securepages patch by bjaspan.


[1]   In fact, setting session.cookie_secure would defeat the purpose of this module, and will give you a warning on your site's status page.