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

Cypress.Commands.add('register', (email, password) => {
    cy.findByRole('link', { name: 'Register' }).click()
    cy.url().should('include', '/register')
    cy.findAllByLabelText("Email").type(email)
    cy.findAllByLabelText("Password").type(password)
    cy.findByRole('button', { name: 'Register' }).click()
    cy.url().should('not.include', '/register')
});


Cypress.Commands.add('login', (email, password) => {
    cy.findByRole('link', { name: 'Login' }).click()
    cy.url().should('include', '/login')
    cy.findAllByLabelText("Email").type(email)
    cy.findAllByLabelText("Password").type(password)
    cy.findByRole('button', { name: 'Login' }).click()
    cy.url().should('not.include', '/login')
});