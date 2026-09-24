(function() {
  var template = Handlebars.template, templates = Handlebars.templates = Handlebars.templates || {};
templates['gameLink'] = template({"compiler":[8,">= 4.3.0"],"main":function(container,depth0,helpers,partials,data) {
    var helper, alias1=depth0 != null ? depth0 : (container.nullContext || {}), alias2=container.hooks.helperMissing, alias3="function", alias4=container.escapeExpression, lookupProperty = container.lookupProperty || function(parent, propertyName) {
        if (Object.prototype.hasOwnProperty.call(parent, propertyName)) {
          return parent[propertyName];
        }
        return undefined
    };

  return "<a href=\""
    + alias4(((helper = (helper = lookupProperty(helpers,"link") || (depth0 != null ? lookupProperty(depth0,"link") : depth0)) != null ? helper : alias2),(typeof helper === alias3 ? helper.call(alias1,{"name":"link","hash":{},"data":data,"loc":{"start":{"line":1,"column":9},"end":{"line":1,"column":17}}}) : helper)))
    + "\" class=\"game-link\" style=\"background-image: url("
    + alias4(((helper = (helper = lookupProperty(helpers,"url") || (depth0 != null ? lookupProperty(depth0,"url") : depth0)) != null ? helper : alias2),(typeof helper === alias3 ? helper.call(alias1,{"name":"url","hash":{},"data":data,"loc":{"start":{"line":1,"column":66},"end":{"line":1,"column":73}}}) : helper)))
    + ");\">\n    <span>"
    + alias4(((helper = (helper = lookupProperty(helpers,"text") || (depth0 != null ? lookupProperty(depth0,"text") : depth0)) != null ? helper : alias2),(typeof helper === alias3 ? helper.call(alias1,{"name":"text","hash":{},"data":data,"loc":{"start":{"line":2,"column":10},"end":{"line":2,"column":18}}}) : helper)))
    + "</span>\n</a>";
},"useData":true});
templates['playerStats'] = template({"compiler":[8,">= 4.3.0"],"main":function(container,depth0,helpers,partials,data) {
    var helper, alias1=depth0 != null ? depth0 : (container.nullContext || {}), alias2=container.hooks.helperMissing, alias3="function", alias4=container.escapeExpression, lookupProperty = container.lookupProperty || function(parent, propertyName) {
        if (Object.prototype.hasOwnProperty.call(parent, propertyName)) {
          return parent[propertyName];
        }
        return undefined
    };

  return "<tr>\n    <td>"
    + alias4(((helper = (helper = lookupProperty(helpers,"username") || (depth0 != null ? lookupProperty(depth0,"username") : depth0)) != null ? helper : alias2),(typeof helper === alias3 ? helper.call(alias1,{"name":"username","hash":{},"data":data,"loc":{"start":{"line":2,"column":8},"end":{"line":2,"column":20}}}) : helper)))
    + "</td>\n    <td>"
    + alias4(((helper = (helper = lookupProperty(helpers,"hangman_wins") || (depth0 != null ? lookupProperty(depth0,"hangman_wins") : depth0)) != null ? helper : alias2),(typeof helper === alias3 ? helper.call(alias1,{"name":"hangman_wins","hash":{},"data":data,"loc":{"start":{"line":3,"column":8},"end":{"line":3,"column":24}}}) : helper)))
    + "</td>\n    <td>"
    + alias4(((helper = (helper = lookupProperty(helpers,"hangman_losses") || (depth0 != null ? lookupProperty(depth0,"hangman_losses") : depth0)) != null ? helper : alias2),(typeof helper === alias3 ? helper.call(alias1,{"name":"hangman_losses","hash":{},"data":data,"loc":{"start":{"line":4,"column":8},"end":{"line":4,"column":26}}}) : helper)))
    + "</td>\n    <td>"
    + alias4(((helper = (helper = lookupProperty(helpers,"tictactoe_games") || (depth0 != null ? lookupProperty(depth0,"tictactoe_games") : depth0)) != null ? helper : alias2),(typeof helper === alias3 ? helper.call(alias1,{"name":"tictactoe_games","hash":{},"data":data,"loc":{"start":{"line":5,"column":8},"end":{"line":5,"column":27}}}) : helper)))
    + "</td>\n    <td>"
    + alias4(((helper = (helper = lookupProperty(helpers,"card_games") || (depth0 != null ? lookupProperty(depth0,"card_games") : depth0)) != null ? helper : alias2),(typeof helper === alias3 ? helper.call(alias1,{"name":"card_games","hash":{},"data":data,"loc":{"start":{"line":6,"column":8},"end":{"line":6,"column":22}}}) : helper)))
    + "</td>\n</tr>";
},"useData":true});
})();