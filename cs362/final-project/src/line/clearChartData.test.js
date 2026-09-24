/**
* @jest-environment jsdom
*/

const fs = require("fs")
require("@testing-library/jest-dom")
const domTesting = require("@testing-library/dom")
const userEvent = require("@testing-library/user-event").default

function initDomFromFiles(htmlPath, jsPath) {
    const html = fs.readFileSync(htmlPath, 'utf-8')
    document.open()
    document.write(html)
    document.close()
    jest.isolateModules(function () {
        require(jsPath)
    })
}

test("clear chart data", async function () {
    initDomFromFiles(`${__dirname}/line.html`, `${__dirname}/line.js`)

    const user = userEvent.setup()

    const clearChartBtn = domTesting.getByText(document, "Clear chart data")
    const addBtn = domTesting.getByTestId(document, "add-values-btn")

    const titleInput = domTesting.getByLabelText(document, "Chart title")
    const xLabelInput = domTesting.getByLabelText(document, "X label")
    const yLabelInput = domTesting.getByLabelText(document, "Y label")
    const colorInput = domTesting.getByLabelText(document, "Chart color")


    await user.type(titleInput, "My Chart")
    await user.type(xLabelInput, "My X Label")
    await user.type(yLabelInput, "My Y Label")

    await user.click(colorInput)
    colorInput.value = '#cc66ff'
    expect(colorInput).toHaveValue('#cc66ff') // verify color change

    await user.click(addBtn)
    const xInputs = domTesting.queryAllByLabelText(document, "X")
    const yInputs = domTesting.queryAllByLabelText(document, "Y")

    await user.type(xInputs[0], '1')
    await user.type(xInputs[1], '2')
    await user.type(yInputs[0], '11')
    await user.type(yInputs[1], '12')

    await user.click(clearChartBtn)

    const newXInputs = domTesting.queryAllByLabelText(document, "X")
    const newYInputs = domTesting.queryAllByLabelText(document, "Y")

    expect(titleInput).toHaveValue("")
    expect(xLabelInput).toHaveValue("")
    expect(yLabelInput).toHaveValue("")
    expect(colorInput).toHaveValue('#ff4500')
    expect(newXInputs).toHaveLength(1)
    expect(newYInputs).toHaveLength(1)
    expect(newXInputs[0]).toHaveValue(null)
    expect(newYInputs[0]).toHaveValue(null)
    
})