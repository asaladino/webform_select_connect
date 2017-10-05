/**
 * Callback used to verify if the connection works.
 */
// noinspection JSUnusedGlobalSymbols
function webform_select_connect_verify() {
  var $fieldset = jQuery(this).parents('fieldset:first');
  var wsc = new WebformSelectConnect();

  wsc.$originSelect = wsc.getField($fieldset.find('input[name=origin_select]').val());
  wsc.$destinationSelect = wsc.getField($fieldset.find('input[name=dest_select]').val());
  wsc.valuePrefix = $fieldset.find('input[name=value_prefix]').val();
  wsc.url = $fieldset.find('input[name=url]').val();
  wsc.nodesName = $fieldset.find('input[name=nodes_name]').val();
  wsc.nodeName = $fieldset.find('input[name=node_name]').val();
  wsc.nodeValue = $fieldset.find('input[name=node_value]').val();
  wsc.nodeTitle = $fieldset.find('input[name=node_title]').val();
  wsc.verifyValue = $fieldset.find('input[name=select_test]').val();

  wsc.verify();
}

/**
 * This object connects the select fields together. When the origin select field
 * changes, the value is used to GET the options for the destination select.
 * @constructor
 */
function WebformSelectConnect() {
}

/**
 * Modify the prototype will all needed fields and properties.
 * @type {{
 *  $originSelect: string,
 *  $destinationSelect: string,
 *  valuePrefix: string,
 *  url: string,
 *  nodesName: string,
 *  nodeName: string,
 *  nodeValue: string,
 *  nodeTitle: string,
 *  verifyValue: number,
 *  getField: WebformSelectConnect.getField,
 *  init: WebformSelectConnect.init,
 *  verify: WebformSelectConnect.verify
 * }}
 */
WebformSelectConnect.prototype = {
  /**
   * Originating select field.
   */
  $originSelect: '',
  /**
   * Destination select field that will be populated.
   */
  $destinationSelect: '',
  /**
   * Additional text that will be stripped from the value.
   */
  valuePrefix: '',
  /**
   * Web service url that will be populating the destination select field.
   * Expected to return json.
   */
  url: '',
  /**
   * Name of the node containing the list of objects. Should be an array.
   */
  nodesName: '',
  /**
   * Name of the node in the json response containing the value and title.
   */
  nodeName: '',
  /**
   * To be saved in the form submission.
   */
  nodeValue: '',
  /**
   * To be displayed in the destination select field.
   */
  nodeTitle: '',
  /**
   * Test value to use during verification.
   */
  verifyValue: 0,

  /**
   * Gets a jquery object for the select field based on the field name.
   * @param name of the field.
   * @returns {jQuery}
   */
  getField: function (name) {
    return jQuery('*[name="submitted[' + name + ']"]');
  },

  /**
   * Initializes the events between the select fields.
   */
  init: function () {
    var $this = this;
    if(this.$destinationSelect.prop("tagName") === 'INPUT'){
      var $select = jQuery('<select name="' + this.$destinationSelect.prop("name") + '" class="form-control form-select"></select>');
      this.$destinationSelect = this.$destinationSelect.replaceWith($select);
      this.$destinationSelect = $select;
    }

    this.$destinationSelect.html('<option>- None -</option>');
    this.$originSelect.change(function () {
      var id = jQuery(this).val().replace($this.valuePrefix, '');
      jQuery.get($this.url + id, function (data) {
        $this.$destinationSelect.html('<option>- None -</option>');
        if (data[$this.nodesName].length > 0) {
          for (var i in data[$this.nodesName]) {
            // noinspection JSUnfilteredForInLoop
            var node = data[$this.nodesName][i][$this.nodeName];
            $this.$destinationSelect.append('<option value="' + node[$this.nodeValue] + '">' + node[$this.nodeTitle] + '</option>');
          }
        }
      });
    });
    this.$originSelect.change();
  },

  /**
   * Verifies that all the params work together.
   */
  verify: function () {
    var $this = this;
    jQuery.get($this.url + $this.verifyValue, function (data) {
      if (data[$this.nodesName].length > 0) {
        // noinspection LoopStatementThatDoesntLoopJS
        for (var i in data[$this.nodesName]) {
          // noinspection JSUnfilteredForInLoop
          var node = data[$this.nodesName][i][$this.nodeName];
          if (node) {
            if (node[$this.nodeValue]) {
              if (node[$this.nodeTitle]) {
                alert('Looks good.');
                return;
              }
              else {
                alert('Problem finding: ' + $this.nodeTitle);
                return;
              }
            }
            else {
              alert('Problem finding: ' + $this.nodeValue);
              return;
            }
          }
          else {
            alert('Problem finding: ' + $this.nodeName);
            return;
          }
        }
      }
      else {
        alert('Problem finding: ' + $this.nodesName);
      }
    });
  }
};
