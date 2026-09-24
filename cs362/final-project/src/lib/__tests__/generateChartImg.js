/**
 * @jest-environment jest-fixed-jsdom
 */

const fs = require('fs')
const generateChartImg = require('../generateChartImg')
const fakeImage = fs.readFileSync(__dirname + '/fakeImage.png')

const http = require("msw").http
const HttpResponse = require("msw").HttpResponse
const setupServer = require("msw/node").setupServer

const server = setupServer(
    http.post('https://quickchart.io/chart', function(){
        return new HttpResponse(fakeImage, {
        headers: { 'Content-Type': 'image/png' }
        })
    })
)

beforeAll(function () {
    server.listen()
})

afterEach(function () { 
    server.resetHandlers()
})

afterAll(function () {
    server.close()
})

test("Returns URL", async function () {
    // Arrange
    const type = 'bar'
    const data = [{x:1, y:2}]
    const xLabel = 'X'
    const yLabel = 'Y'
    
    // Act
    const result = await generateChartImg(type, data, xLabel, yLabel)

    // Assert
    expect(result).toBeDefined()
    expect(typeof result).toBe('string')
    expect(result).toMatch(/^blob:/)
});

test("Returns URL, additional parameters", async function () {
    // Arrange
    const type = 'line'
    const data = [{x:2.718281828459045, y:3.1415926535}]
    const xLabel = 'X'
    const yLabel = 'Y'
    const title = 'MyChart'
    const color = 'blue'
    
    // Act
    const result = await generateChartImg(type, data, xLabel, yLabel, title, color)

    // Assert
    expect(result).toBeDefined()
    expect(typeof result).toBe('string')
    expect(result).toMatch(/^blob:/)
});

test("Returns Error", async function () {
    // Arrange
    const type = 'bar'
    const data = [{x:1, y:2}]
    const xLabel = 'X'
    const yLabel = 'Y'
    
    server.use(
        http.post('https://quickchart.io/chart', function() {
            return new HttpResponse('Error', { status: 500 })
    }))

    // Act & Assert
    await expect(generateChartImg(type, data, xLabel, yLabel)).rejects.toThrow()
});