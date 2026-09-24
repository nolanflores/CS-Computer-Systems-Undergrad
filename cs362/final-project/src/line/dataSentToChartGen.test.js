/**
* @jest-environment jsdom
*/

jest.mock('../lib/generateChartImg', function (){
  return jest.fn().mockResolvedValue('http://picsum.photos/480')
})

const fs = require("fs")
require("@testing-library/jest-dom")
const domTesting = require("@testing-library/dom")
const userEvent = require("@testing-library/user-event").default
const generateChartImg = require("../lib/generateChartImg")

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

test("Data correctly sent to chart generation function", async function () {
    initDomFromFiles(`${__dirname}/line.html`, `${__dirname}/line.js`)
    const user = userEvent.setup()

    const genChartBtn = domTesting.getByText(document, "Generate chart")
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

    await user.click(addBtn)
    const xInputs = domTesting.queryAllByLabelText(document, "X")
    const yInputs = domTesting.queryAllByLabelText(document, "Y")

    await user.type(xInputs[0], '1')
    await user.type(xInputs[1], '2')
    await user.type(yInputs[0], '11')
    await user.type(yInputs[1], '12')

    await user.click(genChartBtn)

    expect(generateChartImg).toHaveBeenCalledWith(
        "line",           // chart type
        [{ x: "1", y: "11" }, { x: "2", y: "12" }],  // data points
        "My X Label",     // x label
        "My Y Label",     // y label
        "My Chart",       // title
        "#cc66ff"         // color
    )
})