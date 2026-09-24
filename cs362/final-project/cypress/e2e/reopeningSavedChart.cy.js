describe("Re-opening a saved chart", function() {
    it("should display all correct chart details and elements when reopened from gallery", function() {
        cy.visit("/")

        cy.clickMenuOption("Line")

        cy.addChartTitle("Powers of 2")
        cy.addXYlabels("x", "2^x")
        cy.typeInLastXYRow("1", "2")
        cy.clickButtonWText("+")
        cy.typeInLastXYRow("2", "4")
        cy.clickButtonWText("+")
        cy.typeInLastXYRow("3", "8")
        cy.clickButtonWText("+")
        cy.typeInLastXYRow("4", "16")

        cy.clickButtonWText("Generate chart")
        cy.clickButtonWText("Save chart")

        cy.clickMenuOption("Gallery")

        cy.findByText("Powers of 2").click()
        cy.url().should("contain", "line")

        cy.confirmChartDisplayed()
        cy.confirmChartTitle("Powers of 2")
        cy.confirmXYlabels("x", "2^x")
        cy.confirmXYvalues("1", "2", 0)
        cy.confirmXYvalues("2", "4", 1)
        cy.confirmXYvalues("3", "8", 2)
        cy.confirmXYvalues("4", "16", 3)
        cy.confirmXYvalues("", "", 4)
    })
})