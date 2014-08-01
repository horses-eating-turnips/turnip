@api
Feature: Content Editors can add basic content (pages)
  In order to separate role responsibilities
  As a Content Editor
  I should be able to add a basic page

  Background:
    Given I am logged in as a user with the "content editor" role

  Scenario: Authenticated user can add a new page
    Given I am at "/node/add/page"
    And I fill in "First page" for "Title"
    And I enter "I am here" for "Body"
    And I press "Save"
    Then I should see the heading "First page"

  Scenario: Authenticated user can edit an existing page
    And I am viewing my "page" node with the title "Second Event"
    Then I click the link "Edit"
    Then I should see the "Save" button

  Scenario: Authenticated user can delete an existing page
    And I am viewing my "page" node with the title "Third Event"
    Then I click the button "Delete"
    Then I should see the "Are you sure you want to delete Third Event" header
