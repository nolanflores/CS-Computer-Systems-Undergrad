describe('registers, logs in, performs 5 calculations, and views history', () => {
    it('view calculation history', () => {
        cy.visit('/')
        cy.register('florenol@oregonstate.edu', 'xyz789XYZ!!!')
        cy.login('florenol@oregonstate.edu', 'xyz789XYZ!!!')

        cy.contains("1").click()
        cy.findByTestId("key-add").click()
        cy.contains("2").click()
        cy.findByTestId("key-add").click()
        cy.contains("3").click()
        cy.findByTestId("key-equals").click()

        cy.contains("6").click()
        cy.findByTestId("key-subtract").click()
        cy.contains("2").click()
        cy.findByTestId("key-equals").click()

        cy.findByTestId("key-multiply").click()
        cy.contains("9").click()
        cy.findByTestId("key-equals").click()

        cy.contains("5").click()
        cy.findByTestId("key-multiply").click()
        cy.contains("9").click()
        cy.findByTestId("key-equals").click()

        cy.findByTestId("key-divide").click()
        cy.contains("5").click()
        cy.findByTestId("key-equals").click()

        cy.findByRole('link', { name: 'History' }).click()
        cy.url().should('include', '/history')

        cy.findByTestId("history-list").children().should("have.length", 5)
        cy.findByTestId("history-list").children().eq(0).should("have.text", "I + II + III = VI")
        cy.findByTestId("history-list").children().eq(1).should("have.text", "VI − II = IIII")
        cy.findByTestId("history-list").children().eq(2).should("have.text", "IIII × VIIII = XXXVI")
        cy.findByTestId("history-list").children().eq(3).should("have.text", "V × VIIII = XXXXV")
        cy.findByTestId("history-list").children().eq(4).should("have.text", "XXXXV ÷ V = VIIII")
    })
})