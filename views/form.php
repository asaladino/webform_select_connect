<?php
/**
 * Initializes the interaction between the select fields.
 *
 * @var array $params
 */
?>
<script>
  (function ($) {
    $(document).ready(function () {
      var wsc = new WebformSelectConnect();
      wsc.$originSelect = wsc.getField('<?php echo $params['extra']['origin_select'] ?>');
      wsc.$destinationSelect = wsc.getField('<?php echo $params['extra']['dest_select'] ?>');
      wsc.valuePrefix = '<?php echo $params['extra']['value_prefix'] ?>';
      wsc.url = '<?php echo $params['extra']['url'] ?>';
      wsc.nodesName = '<?php echo $params['extra']['nodes_name'] ?>';
      wsc.nodeName = '<?php echo $params['extra']['node_name'] ?>';
      wsc.nodeValue = '<?php echo $params['extra']['node_value'] ?>';
      wsc.nodeTitle = '<?php echo $params['extra']['node_title'] ?>';
      wsc.init();
    });
  })(jQuery);
</script>
