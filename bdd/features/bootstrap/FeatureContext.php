<?php

use Behat\Behat\Exception\PendingException,
    Behat\Gherkin\Node\TableNode;
use Drupal\DrupalExtension\Context\DrupalContext;
use Symfony\Component\Process\Process;

use Behat\Behat\Context\Step\Given;
use Behat\Behat\Context\Step\When;
use Behat\Behat\Context\Step\Then;
use Behat\Behat\Event\ScenarioEvent;

use Behat\Mink\Exception\ElementNotFoundException;

require 'vendor/autoload.php';

/**
 * Features context for custom step-definitions.
 */
class FeatureContext extends DrupalContext {
}
