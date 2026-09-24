describe("Chart is correctly generated", function () {
    it("should display a chart image after the user enters data and clicks generate chart", function () {
        cy.visit("/")
        cy.clickMenuOption("Line")

        cy.addChartTitle("My Test Chart")
        cy.addXYlabels("X Axis", "Y Axis")
        cy.typeInLastXYRow("1", "5")

        cy.clickButtonWText("Generate chart")

        cy.confirmChartDisplayed()
    })
})