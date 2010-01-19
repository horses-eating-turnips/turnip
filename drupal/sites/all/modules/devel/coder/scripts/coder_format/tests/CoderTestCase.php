<?php
// $Id: CoderTestCase.php,v 1.1.2.2 2008/09/23 14:35:59 douggreen Exp $

require_once drupal_get_path('module', 'coder') .'/scripts/coder_format/coder_format.inc';

class CoderTestCase extends DrupalWebTestCase {
  function assertFormat($input, $expect) {
    $result = coder_format_string_all($input);
    $this->assertIdentical($result, $input);
  }
}

