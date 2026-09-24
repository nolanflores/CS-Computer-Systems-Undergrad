// ***********************************************
// This example commands.js shows you how to
// create various custom commands and overwrite
// existing commands.
//
// For more comprehensive examples of custom
// commands please read more here:
// https://on.cypress.io/custom-commands
// ***********************************************
//
//
// -- This is a parent command --
// Cypress.Commands.add('login', (email, password) => { ... })
//
//
// -- This is a child command --
// Cypress.Commands.add('drag', { prevSubject: 'element'}, (subject, options) => { ... })
//
//
// -- This is a dual command --
// Cypress.Commands.add('dismiss', { prevSubject: 'optional'}, (subject, options) => { ... })
//
//
// -- This will overwrite an existing command --
// Cypress.Commands.overwrite('visit', (originalFn, url, options) => { ... })

require("@testing-library/cypress/add-commands")

Cypress.Commands.add("clickMenuOption", function(option) {
    cy.findByRole("link", {
        name: option
    }).click()
})

Cypress.Commands.add("clickButtonWText", function(buttonText) {
    cy.findByRole("button", {
        name: buttonText
    }).click()
})

Cypress.Commands.add("addChartTitle", function(title) {
    cy.findByLabelText("Chart title").type(title)
})

Cypress.Commands.add("confirmChartTitle", function(title) {
    cy.findByLabelText("Chart title").should("have.value", title)
})

Cypress.Commands.add("addXYlabels", function(xLabel, yLabel) {
    cy.findByLabelText("X label").type(xLabel)
    cy.findByLabelText("Y label").type(yLabel)
})

Cypress.Commands.add("confirmXYlabels", function(xLabel, yLabel) {
    cy.findByLabelText("X label").should("have.value", xLabel)
    cy.findByLabelText("Y label").should("have.value", yLabel)
})

Cypress.Commands.add("typeInLastXYRow", function(x, y) {
    cy.findAllByLabelText("X").last().type(x)
    cy.findAllByLabelText("Y").last().type(y)
})

Cypress.Commands.add("confirmXYvalues", function(x, y, n) {
    cy.findAllByLabelText("X")
        .eq(n)
        .should("have.value", x)

    cy.findAllByLabelText("Y")
        .eq(n)
        .should("have.value", y)
})

Cypress.Commands.add("confirmChartDisplayed", function() {
    cy.findAllByRole("img")
        .parents("[data-testid*='chartImage']")
        .should("exist")
})

Cypress.Commands.add("setChartColor", function(color) {
    cy.findByLabelText("Chart color")
        .invoke("val", color)
        .trigger("change")
})

Cypress.Commands.add("confirmChartColor", function(color) {
    cy.findByLabelText("Chart color")
        .should("have.value", color)
})

Cypress.Commands.add("confirmChartDisplayed", function() {
    cy.get("img", { timeout: 10000 }).should("exist").and("be.visible")
})