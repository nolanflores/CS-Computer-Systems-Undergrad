describe("Save Chart to Gallery", function() {
    it("Should display the saved chart within the gallery.", function() {
        cy.visit("/")

        cy.clickMenuOption("Line")

        cy.addChartTitle("Powers of 3")
        cy.addXYlabels("x", "3^x")
        cy.typeInLastXYRow("1", "3")
        cy.clickButtonWText("+")
        cy.typeInLastXYRow("2", "9")
        cy.clickButtonWText("+")
        cy.typeInLastXYRow("3", "27")
        cy.clickButtonWText("+")
        cy.typeInLastXYRow("4", "81")

        cy.clickButtonWText("Generate chart")
        cy.clickButtonWText("Save chart")

        cy.clickMenuOption("Gallery")

        cy.findByText("Powers of 3").should("exist").and("be.visible")
    })
})