#!/usr/bin/perl -w

use lib '../scripts';
use PasswordParser;

$SQL_FILE = $ARGV[0] || 0;

unless (-e $SQL_FILE) {
  print "\nusage: $0 SQL_FILE (SQL_FILE must be gzipped)\n\n";
  exit;
}

$Y = PasswordParser::parseEncrypted('../../conf/pass.yml.gpg');

`scp $SQL_FILE $$Y{'test server'}{'webhost'}{'hostname'}:`;


print `ssh $$Y{'test server'}{'webhost'}{'hostname'} \\
"mysqladmin \\
-u $$Y{'test server'}{'dbhost'}{'user'} \\
-p$$Y{'test server'}{'dbhost'}{'pass'} \\
-h$$Y{'test server'}{'dbhost'}{'hostname'} \\
-f drop $$Y{'test server'}{'dbhost'}{'dbname'} ; \\
mysqladmin \\
-u $$Y{'test server'}{'dbhost'}{'user'} \\
-p$$Y{'test server'}{'dbhost'}{'pass'} \\
-h$$Y{'test server'}{'dbhost'}{'hostname'} \\
create $$Y{'test server'}{'dbhost'}{'dbname'} ; \\
gzip -dc $SQL_FILE | mysql \\
-u $$Y{'test server'}{'dbhost'}{'user'} \\
-p$$Y{'test server'}{'dbhost'}{'pass'} \\
-h$$Y{'test server'}{'dbhost'}{'hostname'} \\
$$Y{'test server'}{'dbhost'}{'dbname'} \
"`;


