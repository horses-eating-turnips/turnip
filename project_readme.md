# PROJECTNAME
PROJECTDESCRIPTION

## Deployment plan

### Credentials

**Server** http://example.com/ (127.0.0.1)

**Username** root

### Drush config

```php
$aliases['example'] = array(
  'root' => '/var/www/example.com',
  'uri' => 'example.com',
  'remote-host' => 'example.com',
  'remote-user' => 'root',
);
```

### SSH config

```
Host example
  Hostname example.com
  User deploy
```

### Deployment process

Run within the project root:

```sh
drush @example sql-dump --result-file=production_current.sql --gzip
scp example:/var/www/example.com/production_current.sql.gz db/
ssh example 'rm /var/www/example.com/production_current.sql.gz'
```

Next, load the database into your local site and test database updates, features
reverts, etc., on the most recent database. If everything works:

```sh
bin/deploy_to_production
drush @example updb
```

## Implementation Plan

### Content Types

* Basic page
* Article

### Feature X

#### Feature dependencies

* Feature Y

#### Content Type dependencies

* Article

#### Role dependencies

* Content creator
* Content reviewer
* Content publisher

#### Workflow

1. *Content creator* user creates an Article in *Draft*.
1. *Content creator* sets the Article to *Ready for review*.
1. *Content reviewer* sets the Article to either *Draft* or *Ready to publish*.
1. *Content publisher* sets the Article to *Published*.
1. The Article shows up in the appropriate views.

#### Views

##### News Feed

* **Content pane** A listing of recent published Articles.

#### Permissions

##### Create own article content

* Content creator

##### Edit own article content

* Content creator

##### Moderate all content from *Draft* to *Ready for review*

* Content creator
* Content reviewer

##### Moderate all content from *Ready for review* to *Draft*

* Content creator
* Content reviewer
* Content publisher

##### Moderate all content from *Ready for review* to *Ready to publish*

* Content reviewer
* Content publisher

##### Moderate all content from *Ready to publish* to *Draft*

* Content reviewer
* Content publisher

##### Moderate all content from *Ready to publish* to *Published*

* Content publisher
