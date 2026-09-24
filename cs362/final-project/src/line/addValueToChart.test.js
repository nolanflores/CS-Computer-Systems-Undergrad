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

test("clicking the add values button adds a new empty row of inputs", async function () {
    initDomFromFiles(`${__dirname}/line.html`, `${__dirname}/line.js`)
    const user = userEvent.setup()

    const addBtn = domTesting.getByTestId(document, "add-values-btn")
    const xInputs = domTesting.queryAllByLabelText(document, "X")
    const yInputs = domTesting.queryAllByLabelText(document, "Y")

    const numberOfInputs = xInputs.length
    expect(yInputs).toHaveLength(numberOfInputs)

    await user.click(addBtn)

    const xInputsAfter = domTesting.queryAllByLabelText(document, "X")
    const yInputsAfter = domTesting.queryAllByLabelText(document, "Y")

    expect(xInputsAfter).toHaveLength(numberOfInputs + 1)
    expect(yInputsAfter).toHaveLength(numberOfInputs + 1)
    expect(xInputsAfter[numberOfInputs]).not.toHaveValue()
    expect(yInputsAfter[numberOfInputs]).not.toHaveValue()
})

test("clicking the add values button multiple times adds multiple new empty rows of inputs", async function () {
    initDomFromFiles(`${__dirname}/line.html`, `${__dirname}/line.js`)
    const user = userEvent.setup()

    const addBtn = domTesting.getByTestId(document, "add-values-btn")
    const xInputs = domTesting.queryAllByLabelText(document, "X")
    const yInputs = domTesting.queryAllByLabelText(document, "Y")

    const numberOfInputs = xInputs.length
    expect(yInputs).toHaveLength(numberOfInputs)

    await user.click(addBtn)
    await user.click(addBtn)

    const xInputsAfter = domTesting.queryAllByLabelText(document, "X")
    const yInputsAfter = domTesting.queryAllByLabelText(document, "Y")

    expect(xInputsAfter).toHaveLength(numberOfInputs + 2)
    expect(yInputsAfter).toHaveLength(numberOfInputs + 2)
    expect(xInputsAfter[numberOfInputs]).not.toHaveValue()
    expect(yInputsAfter[numberOfInputs]).not.toHaveValue()
    expect(xInputsAfter[numberOfInputs + 1]).not.toHaveValue()
    expect(yInputsAfter[numberOfInputs + 1]).not.toHaveValue()
})

test("clicking the add values button doesn't affect existing rows", async function () {
    initDomFromFiles(`${__dirname}/line.html`, `${__dirname}/line.js`)
    const user = userEvent.setup()

    const addBtn = domTesting.getByTestId(document, "add-values-btn")

    await user.click(addBtn)
    await user.click(addBtn)

    const xInputs = domTesting.queryAllByLabelText(document, "X")
    const yInputs = domTesting.queryAllByLabelText(document, "Y")
    const numberOfInputs = xInputs.length

    await user.type(xInputs[numberOfInputs - 1], "5")
    await user.type(yInputs[numberOfInputs - 1], "10")
    await user.type(yInputs[numberOfInputs - 2], "3")
    await user.click(addBtn)

    expect(xInputs[numberOfInputs - 1]).toHaveValue(5)
    expect(yInputs[numberOfInputs - 1]).toHaveValue(10)
    expect(xInputs[numberOfInputs - 2]).not.toHaveValue()
    expect(yInputs[numberOfInputs - 2]).toHaveValue(3)
})