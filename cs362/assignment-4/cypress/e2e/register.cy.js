describe('register a new user', () => {
    it('passes', () => {
        cy.visit('/')
        cy.register('florenol@oregonstate.edu', 'xyz789XYZ!!!')
        cy.findByRole('link', { name: 'Login' }).should('be.visible')
    })
})