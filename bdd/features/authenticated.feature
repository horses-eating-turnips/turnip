@api
Feature: Basic authenticated user functionality
  In order to prove that this site is functional for logged in users
  As a user
  I need to be able to edit my account
    And I need to be able to log out of the site

  Background: 
   Given I am logged in as a user with the "authenticated user" role

  Scenario: Authenticated user edit their account
    Given I am at "/"
    When I click "My account"
    Then I should see the link "Edit"

  Scenario: Authenticated user can see a logout link
    When I visit "/"
    Then I should see the link "Log out"
