describe('register a new user and login', () => {
    it('login user', () => {
        cy.visit('/')
        cy.register('florenol@oregonstate.edu', 'xyz789XYZ!!!')
        cy.login('florenol@oregonstate.edu', 'xyz789XYZ!!!')
        cy.findByRole('link', { name: 'Logout' }).should('be.visible')
        cy.findByRole('link', { name: 'History' }).should('be.visible')
        cy.findByRole('link', { name: 'Unregister' }).should('be.visible')
    })
})