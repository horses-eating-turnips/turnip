Feature: Basic anonymous site functionality
  In order to prove that this site has been setup successfully
  As an anonymous user
  I need to see a home page

  Background:
    Given I am an anonymous user

    Scenario: Anonymous user can see the home page
      When I visit "/"
      Then I should get a "200" HTTP response
