(function() {
  var template = Handlebars.template, templates = Handlebars.templates = Handlebars.templates || {};
templates['post'] = template({"compiler":[8,">= 4.3.0"],"main":function(container,depth0,helpers,partials,data) {
    var helper, alias1=depth0 != null ? depth0 : (container.nullContext || {}), alias2=container.hooks.helperMissing, alias3="function", alias4=container.escapeExpression, lookupProperty = container.lookupProperty || function(parent, propertyName) {
        if (Object.prototype.hasOwnProperty.call(parent, propertyName)) {
          return parent[propertyName];
        }
        return undefined
    };

  return "<div class=\"post\" data-price=\""
    + alias4(((helper = (helper = lookupProperty(helpers,"price") || (depth0 != null ? lookupProperty(depth0,"price") : depth0)) != null ? helper : alias2),(typeof helper === alias3 ? helper.call(alias1,{"name":"price","hash":{},"data":data,"loc":{"start":{"line":1,"column":30},"end":{"line":1,"column":39}}}) : helper)))
    + "\" data-city=\""
    + alias4(((helper = (helper = lookupProperty(helpers,"city") || (depth0 != null ? lookupProperty(depth0,"city") : depth0)) != null ? helper : alias2),(typeof helper === alias3 ? helper.call(alias1,{"name":"city","hash":{},"data":data,"loc":{"start":{"line":1,"column":52},"end":{"line":1,"column":60}}}) : helper)))
    + "\" data-condition=\""
    + alias4(((helper = (helper = lookupProperty(helpers,"condition") || (depth0 != null ? lookupProperty(depth0,"condition") : depth0)) != null ? helper : alias2),(typeof helper === alias3 ? helper.call(alias1,{"name":"condition","hash":{},"data":data,"loc":{"start":{"line":1,"column":78},"end":{"line":1,"column":91}}}) : helper)))
    + "\">\n    <div class=\"post-contents\">\n        <div class=\"post-image-container\">\n            <img src=\""
    + alias4(((helper = (helper = lookupProperty(helpers,"photoURL") || (depth0 != null ? lookupProperty(depth0,"photoURL") : depth0)) != null ? helper : alias2),(typeof helper === alias3 ? helper.call(alias1,{"name":"photoURL","hash":{},"data":data,"loc":{"start":{"line":4,"column":22},"end":{"line":4,"column":34}}}) : helper)))
    + "\" alt=\""
    + alias4(((helper = (helper = lookupProperty(helpers,"description") || (depth0 != null ? lookupProperty(depth0,"description") : depth0)) != null ? helper : alias2),(typeof helper === alias3 ? helper.call(alias1,{"name":"description","hash":{},"data":data,"loc":{"start":{"line":4,"column":41},"end":{"line":4,"column":56}}}) : helper)))
    + "\">\n        </div>\n        <div class=\"post-info-container\">\n            <a href=\"#\" class=\"post-title\">"
    + alias4(((helper = (helper = lookupProperty(helpers,"description") || (depth0 != null ? lookupProperty(depth0,"description") : depth0)) != null ? helper : alias2),(typeof helper === alias3 ? helper.call(alias1,{"name":"description","hash":{},"data":data,"loc":{"start":{"line":7,"column":43},"end":{"line":7,"column":58}}}) : helper)))
    + "</a> <span class=\"post-price\">$"
    + alias4(((helper = (helper = lookupProperty(helpers,"price") || (depth0 != null ? lookupProperty(depth0,"price") : depth0)) != null ? helper : alias2),(typeof helper === alias3 ? helper.call(alias1,{"name":"price","hash":{},"data":data,"loc":{"start":{"line":7,"column":89},"end":{"line":7,"column":98}}}) : helper)))
    + "</span> <span class=\"post-city\">("
    + alias4(((helper = (helper = lookupProperty(helpers,"city") || (depth0 != null ? lookupProperty(depth0,"city") : depth0)) != null ? helper : alias2),(typeof helper === alias3 ? helper.call(alias1,{"name":"city","hash":{},"data":data,"loc":{"start":{"line":7,"column":131},"end":{"line":7,"column":139}}}) : helper)))
    + ")</span>\n        </div>\n    </div>\n</div>";
},"useData":true});
})();