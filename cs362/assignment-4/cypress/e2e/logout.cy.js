describe('registers, logins, and asserts a proper log out', () => {
    it('logout a user', () => {
        cy.visit('/')
        cy.register('florenol@oregonstate.edu', 'xyz789XYZ!!!')
        cy.login('florenol@oregonstate.edu', 'xyz789XYZ!!!')

        cy.findByRole('link', { name: 'Logout' }).click()

        cy.location('pathname').should('eq', '/')
        cy.findByRole('link', { name: 'Login' }).should('be.visible')
    })
})