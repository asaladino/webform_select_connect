<?php
/**
 * Gets displayed on the webform editor that describes the connection.
 * @var array $component
 * @var array $params
 */
$component = $params['#webform_component'];
?>
<div class='webform-select-connect-info'>
  <strong>Select Connect: </strong> <em><?php echo $component['name'] ?></em>
  <u>from</u>
  <em><?php echo $component['extra']['origin_select'] ?></em>
  <u>to</u>
  <em><?php echo $component['extra']['dest_select'] ?></em>
</div>
