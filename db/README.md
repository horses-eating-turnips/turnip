The following drush command can be used to synchronize a local
database to the test server.

`drush sql-sync @local @test`

Where `@local` is the alias of your local db, and `@test` is the alias
of the test server.

Note that this assumes you have the test server setup as a drush
alias. For gargravarr aliases, see
https://github.com/opensourcery/opensourcery/tree/master/drush.gargravarr.
