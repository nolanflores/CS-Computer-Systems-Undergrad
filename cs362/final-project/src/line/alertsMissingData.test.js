/**
* @jest-environment jsdom
*/

const fs = require("fs")
require("@testing-library/jest-dom")
const domTesting = require("@testing-library/dom")
const userEvent = require("@testing-library/user-event").default

function initDomFromFiles(htmlPath, jsPath) {
    window.localStorage.clear()
    const html = fs.readFileSync(htmlPath, 'utf-8')
    document.open()
    document.write(html)
    document.close()
    jest.isolateModules(function () {
        require(jsPath)
    })
}

describe("Alerts are being displayed", function () {
    test("Alert displayed when both labels and values are missing", async function () {
        initDomFromFiles(`${__dirname}/line.html`, `${__dirname}/line.js`)
        const user = userEvent.setup()

        const spy = jest.spyOn(window, "alert")
        spy.mockImplementation(function () {})

        const generateChartBtn = domTesting.getByTestId(document, "generate-chart-btn")
        const xLabelInput = domTesting.getByLabelText(document, "X label")
        const yLabelInput = domTesting.getByLabelText(document, "Y label")
        const xInputs = domTesting.queryAllByLabelText(document, "X")
        const yInputs = domTesting.queryAllByLabelText(document, "Y")

        expect(xInputs).toHaveLength(1)
        expect(yInputs).toHaveLength(1)

        await user.clear(xInputs[0])
        await user.clear(yInputs[0])
        await user.clear(xLabelInput)
        await user.clear(yLabelInput)

        await user.click(generateChartBtn)

        expect(spy).toHaveBeenCalledTimes(1)

        spy.mockRestore()
    })


    test("Alert displayed when only labels are missing", async function () {
        initDomFromFiles(`${__dirname}/line.html`, `${__dirname}/line.js`)
        const user = userEvent.setup()

        const spy = jest.spyOn(window, "alert")
        spy.mockImplementation(function () {})

        const generateChartBtn = domTesting.getByTestId(document, "generate-chart-btn")
        const xLabelInput = domTesting.getByLabelText(document, "X label")
        const yLabelInput = domTesting.getByLabelText(document, "Y label")
        const xInputs = domTesting.queryAllByLabelText(document, "X")
        const yInputs = domTesting.queryAllByLabelText(document, "Y")

        expect(xInputs).toHaveLength(1)
        expect(yInputs).toHaveLength(1)

        await user.clear(xLabelInput)
        await user.clear(yLabelInput)

        await user.type(xInputs[0], "5")
        await user.type(yInputs[0], "10")

        await user.click(generateChartBtn)

        expect(spy).toHaveBeenCalledTimes(1)

        spy.mockRestore()
    })

    test("Alert displayed when only values are missing", async function () {
        initDomFromFiles(`${__dirname}/line.html`, `${__dirname}/line.js`)
        const user = userEvent.setup()

        const spy = jest.spyOn(window, "alert")
        spy.mockImplementation(function () {})

        const generateChartBtn = domTesting.getByTestId(document, "generate-chart-btn")
        const xLabelInput = domTesting.getByLabelText(document, "X label")
        const yLabelInput = domTesting.getByLabelText(document, "Y label")
        const xInputs = domTesting.queryAllByLabelText(document, "X")
        const yInputs = domTesting.queryAllByLabelText(document, "Y")

        expect(xInputs).toHaveLength(1)
        expect(yInputs).toHaveLength(1)

        await user.clear(xInputs[0])
        await user.clear(yInputs[0])

        await user.type(xLabelInput, "A")
        await user.type(yLabelInput, "B")

        await user.click(generateChartBtn)

        expect(spy).toHaveBeenCalledTimes(1)
        
        spy.mockRestore()
    })
})

describe("Alerts display correct message", function () {
    test("Label alert message displayed when trying to generate chart without labels but with values", async function () {
        initDomFromFiles(`${__dirname}/line.html`, `${__dirname}/line.js`)
        const user = userEvent.setup()

        const spy = jest.spyOn(window, "alert")
        spy.mockImplementation(function () {})

        const generateChartBtn = domTesting.getByTestId(document, "generate-chart-btn")
        const xLabelInput = domTesting.getByLabelText(document, "X label")
        const yLabelInput = domTesting.getByLabelText(document, "Y label")
        const xInputs = domTesting.queryAllByLabelText(document, "X")
        const yInputs = domTesting.queryAllByLabelText(document, "Y")

        expect(xInputs).toHaveLength(1)
        expect(yInputs).toHaveLength(1)

        await user.clear(xLabelInput)
        await user.clear(yLabelInput)

        await user.type(xInputs[0], "5")
        await user.type(yInputs[0], "10")

        await user.click(generateChartBtn)

        expect(spy.mock.lastCall[0]).toBe("Error: Must specify a label for both X and Y!")

        spy.mockRestore()
    })

    test("Values alert message displayed when trying to generate chart without values but with labels", async function () {
        initDomFromFiles(`${__dirname}/line.html`, `${__dirname}/line.js`)
        const user = userEvent.setup()

        const spy = jest.spyOn(window, "alert")
        spy.mockImplementation(function () {})

        const generateChartBtn = domTesting.getByTestId(document, "generate-chart-btn")
        const xLabelInput = domTesting.getByLabelText(document, "X label")
        const yLabelInput = domTesting.getByLabelText(document, "Y label")
        const xInputs = domTesting.queryAllByLabelText(document, "X")
        const yInputs = domTesting.queryAllByLabelText(document, "Y")

        expect(xInputs).toHaveLength(1)
        expect(yInputs).toHaveLength(1)

        await user.clear(xInputs[0])
        await user.clear(yInputs[0])

        await user.type(xLabelInput, "A")
        await user.type(yLabelInput, "B")

        await user.click(generateChartBtn)

        expect(spy.mock.lastCall[0]).toBe("Error: No data specified!")

        spy.mockRestore()
    })

    test("Values alert message displayed when trying to generate chart without both values and labels", async function () {
        initDomFromFiles(`${__dirname}/line.html`, `${__dirname}/line.js`)
        const user = userEvent.setup()

        const spy = jest.spyOn(window, "alert")
        spy.mockImplementation(function () {})

        const generateChartBtn = domTesting.getByTestId(document, "generate-chart-btn")
        const xLabelInput = domTesting.getByLabelText(document, "X label")
        const yLabelInput = domTesting.getByLabelText(document, "Y label")
        const xInputs = domTesting.queryAllByLabelText(document, "X")
        const yInputs = domTesting.queryAllByLabelText(document, "Y")

        expect(xInputs).toHaveLength(1)
        expect(yInputs).toHaveLength(1)

        await user.clear(xInputs[0])
        await user.clear(yInputs[0])
        await user.clear(xLabelInput)
        await user.clear(yLabelInput)

        await user.click(generateChartBtn)

        expect(spy.mock.lastCall[0]).toBe("Error: No data specified!")

        spy.mockRestore()
    })
})




