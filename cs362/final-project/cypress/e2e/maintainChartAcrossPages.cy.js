describe("Chart data is maintained across pages", function() {
    it("Data entered on the building pages should persist when navigating to different chart building pages", function() {
        cy.visit("/")
        cy.clickMenuOption("Line")

        cy.addChartTitle("Maintain Test Chart")
        cy.setChartColor("#008000")
        cy.addXYlabels("Foo", "Bar")

        cy.typeInLastXYRow("1", "2")
        cy.clickButtonWText("+")
        cy.typeInLastXYRow("6", "4")
        cy.clickButtonWText("+")
        cy.typeInLastXYRow("17", "76")
        cy.clickButtonWText("+")
        cy.typeInLastXYRow("11", "12")
        cy.clickButtonWText("+")

        function confirmDataPersisted() {
            cy.confirmChartTitle("Maintain Test Chart")
            cy.confirmChartColor("#008000")
            cy.confirmXYlabels("Foo", "Bar")
            cy.confirmXYvalues("1", "2", 0)
            cy.confirmXYvalues("6", "4", 1)
            cy.confirmXYvalues("17", "76", 2)
            cy.confirmXYvalues("11", "12", 3)
            cy.confirmXYvalues("", "", 4)
        }

        cy.clickMenuOption("Scatter")
        confirmDataPersisted()

        cy.clickMenuOption("Bar")
        confirmDataPersisted()
    })
})