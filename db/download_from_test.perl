#!/usr/bin/perl -w

use lib '../scripts';
use PasswordParser;

$PASS_GPG = "../../conf/pass.yml.gpg";

$Y = PasswordParser::parseEncrypted($PASS_GPG);

$user = $$Y{'test server'}{'webhost'}{'user'};
$host = $$Y{'test server'}{'webhost'}{'hostname'};
$dbuser = $$Y{'test server'}{'dbhost'}{'user'};
$dbpass = $$Y{'test server'}{'dbhost'}{'pass'};
$dbhost = $$Y{'test server'}{'dbhost'}{'hostname'};
$dbname = $$Y{'test server'}{'dbhost'}{'dbname'};

print "Downloading $dbname from $dbhost....\n\n";

`ssh $user\@$host "mysqldump -u $dbuser -p$dbpass -h $dbhost $dbname | gzip" > test_current.sql.gz`;

