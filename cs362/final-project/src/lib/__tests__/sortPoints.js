const sortPoints = require('../sortPoints')

test("returns empty array when given empty array", function () {
    //Arrange -- set up points to be tested
    const points = [ ]

    //Act -- sort points
    const result = sortPoints(points)

    //Assert -- verify that empty array is returned
    expect(result).toEqual(points)
})

test("leaves single point unchanged", function () {
    //Arrange -- set up points to be tested
    const points = [
        { x: 0, y: 0 }
    ]

    //Act -- sort points
    const result = sortPoints(points)

    //Assert -- verify that single point is unchanged
    expect(result).toEqual(points)
})

test("leaves sorted array by ascending X value unchanged, ignoring descending Y values", function () {
    //Arrange -- set up points to be tested
    const points = [
        { x: 0, y: 9 },
        { x: 1, y: 8 },
        { x: 2, y: 7 },
        { x: 3, y: 6 },
        { x: 4, y: 5 },
        { x: 5, y: 4 },
        { x: 6, y: 3 },
        { x: 7, y: 2 },
        { x: 8, y: 1 },
        { x: 9, y: 0 }
    ]

    //Act -- sort points
    const result = sortPoints(points)

    //Assert -- verify that sorted array is unchanged
    expect(result).toEqual(points)
})

test("sorts unsorted array of points by ascending X value", function () {
    //Arrange -- set up points to be tested and expected result
    const points = [
        { x: 9, y: 3 },
        { x: 8, y: 2 },
        { x: 7, y: 2 },
        { x: 6, y: 3 },
        { x: 5, y: 5 },
        { x: 4, y: 6 },
        { x: 3, y: 6 },
        { x: 2, y: 5 },
        { x: 1, y: 9 },
        { x: 0, y: 7 }
    ]
    
    const expected = [
        { x: 0, y: 7 },
        { x: 1, y: 9 },
        { x: 2, y: 5 },
        { x: 3, y: 6 },
        { x: 4, y: 6 },
        { x: 5, y: 5 },
        { x: 6, y: 3 },
        { x: 7, y: 2 },
        { x: 8, y: 2 },
        { x: 9, y: 3 }
    ]

    //Act -- sort points
    const result = sortPoints(points)

    //Assert -- verify that unsorted array is sorted correctly
    expect(result).toEqual(expected)
})

test("leaves matching X values near each other", function () {
    //Arrange -- set up points to be tested and expected result
    const points = [
        { x: 2, y: 3 },
        { x: 1, y: 8 },
        { x: 1, y: 7 },
        { x: 0, y: 9 }
    ]

    const expectedX = [ 0, 1, 1, 2 ]

    //Act -- sort points
    const resultX = sortPoints(points).map(p => p.x)

    //Assert -- verify that matching X values are left in place, ignoring Y values
    expect(resultX).toEqual(expectedX)
})

test("correctly handles negative X values", function () {
    //Arrange -- set up points to be tested and expected result
    const points = [
        { x: 4, y: 3 },
        { x: 3, y: 2 },
        { x: 2, y: 2 },
        { x: 1, y: 3 },
        { x: 0, y: 5 },
        { x: -1, y: 6 },
        { x: -2, y: 6 },
        { x: -3, y: 5 },
        { x: -4, y: 9 },
        { x: -5, y: 7 }
    ]

    const expected = [
        { x: -5, y: 7 },
        { x: -4, y: 9 },
        { x: -3, y: 5 },
        { x: -2, y: 6 },
        { x: -1, y: 6 },
        { x: 0, y: 5 },
        { x: 1, y: 3 },
        { x: 2, y: 2 },
        { x: 3, y: 2 },
        { x: 4, y: 3 }
    ]

    //Act -- sort points
    const result = sortPoints(points)

    //Assert -- verify that negative X values are sorted correctly
    expect(result).toEqual(expected)
})

test("correctly sorts 100 unsorted points", function () {
    //Arrange -- set up 100 points to be tested and expected result
    const points = [
        { x: 99, y: 7 },
        { x: 98, y: 2 },
        { x: 97, y: 9 },
        { x: 96, y: 4 },
        { x: 95, y: 1 },
        { x: 94, y: 6 },
        { x: 93, y: 3 },
        { x: 92, y: 8 },
        { x: 91, y: 5 },
        { x: 90, y: 0 },
        { x: 89, y: 4 },
        { x: 88, y: 9 },
        { x: 87, y: 2 },
        { x: 86, y: 6 },
        { x: 85, y: 1 },
        { x: 84, y: 7 },
        { x: 83, y: 3 },
        { x: 82, y: 8 },
        { x: 81, y: 5 },
        { x: 80, y: 0 },
        { x: 79, y: 2 },
        { x: 78, y: 6 },
        { x: 77, y: 9 },
        { x: 76, y: 1 },
        { x: 75, y: 4 },
        { x: 74, y: 7 },
        { x: 73, y: 3 },
        { x: 72, y: 8 },
        { x: 71, y: 5 },
        { x: 70, y: 0 },
        { x: 69, y: 9 },
        { x: 68, y: 1 },
        { x: 67, y: 6 },
        { x: 66, y: 2 },
        { x: 65, y: 7 },
        { x: 64, y: 4 },
        { x: 63, y: 3 },
        { x: 62, y: 8 },
        { x: 61, y: 5 },
        { x: 60, y: 0 },
        { x: 59, y: 1 },
        { x: 58, y: 9 },
        { x: 57, y: 2 },
        { x: 56, y: 6 },
        { x: 55, y: 4 },
        { x: 54, y: -7 },
        { x: 53, y: 3 },
        { x: 52, y: 8 },
        { x: 51, y: -5 },
        { x: 50, y: 0 },
        { x: 49, y: -6 },
        { x: 48, y: 2 },
        { x: 47, y: 9 },
        { x: 46, y: 1 },
        { x: 45, y: 7 },
        { x: 44, y: 4 },
        { x: 43, y: 3 },
        { x: 42, y: 8 },
        { x: 41, y: 5 },
        { x: 40, y: 0 },
        { x: 39, y: 9 },
        { x: 38, y: 1 },
        { x: 37, y: 6 },
        { x: 36, y: 2 },
        { x: 35, y: 7 },
        { x: 34, y: 4 },
        { x: 33, y: 3 },
        { x: 32, y: 8 },
        { x: 31, y: 5 },
        { x: 30, y: 0 },
        { x: 29, y: 2 },
        { x: 28, y: 9 },
        { x: 27, y: 1 },
        { x: 26, y: 6 },
        { x: 25, y: 7 },
        { x: 24, y: 4 },
        { x: 23, y: 3 },
        { x: 22, y: 8 },
        { x: 21, y: 5 },
        { x: 20, y: 0 },
        { x: 19, y: 6 },
        { x: 18, y: 2 },
        { x: 17, y: 9 },
        { x: 16, y: 1 },
        { x: 15, y: 7 },
        { x: 14, y: 4 },
        { x: 13, y: 3 },
        { x: 12, y: 8 },
        { x: 11, y: 5 },
        { x: 10, y: 0 },
        { x: 9, y: 9 },
        { x: 8, y: 1 },
        { x: 7, y: 6 },
        { x: 6, y: 2 },
        { x: 5, y: 7 },
        { x: 4, y: 4 },
        { x: 3, y: 3 },
        { x: 2, y: 8 },
        { x: 1, y: 5 },
        { x: 0, y: 0 },
    ];

    const expected = [
        { x: 0, y: 0 },
        { x: 1, y: 5 },
        { x: 2, y: 8 },
        { x: 3, y: 3 },
        { x: 4, y: 4 },
        { x: 5, y: 7 },
        { x: 6, y: 2 },
        { x: 7, y: 6 },
        { x: 8, y: 1 },
        { x: 9, y: 9 },
        { x: 10, y: 0 },
        { x: 11, y: 5 },
        { x: 12, y: 8 },
        { x: 13, y: 3 },
        { x: 14, y: 4 },
        { x: 15, y: 7 },
        { x: 16, y: 1 },
        { x: 17, y: 9 },
        { x: 18, y: 2 },
        { x: 19, y: 6 },
        { x: 20, y: 0 },
        { x: 21, y: 5 },
        { x: 22, y: 8 },
        { x: 23, y: 3 },
        { x: 24, y: 4 },
        { x: 25, y: 7 },
        { x: 26, y: 6 },
        { x: 27, y: 1 },
        { x: 28, y: 9 },
        { x: 29, y: 2 },
        { x: 30, y: 0 },
        { x: 31, y: 5 },
        { x: 32, y: 8 },
        { x: 33, y: 3 },
        { x: 34, y: 4 },
        { x: 35, y: 7 },
        { x: 36, y: 2 },
        { x: 37, y: 6 },
        { x: 38, y: 1 },
        { x: 39, y: 9 },
        { x: 40, y: 0 },
        { x: 41, y: 5 },
        { x: 42, y: 8 },
        { x: 43, y: 3 },
        { x: 44, y: 4 },
        { x: 45, y: 7 },
        { x: 46, y: 1 },
        { x: 47, y: 9 },
        { x: 48, y: 2 },
        { x: 49, y: -6 },
        { x: 50, y: 0 },
        { x: 51, y: -5 },
        { x: 52, y: 8 },
        { x: 53, y: 3 },
        { x: 54, y: -7 },
        { x: 55, y: 4 },
        { x: 56, y: 6 },
        { x: 57, y: 2 },
        { x: 58, y: 9 },
        { x: 59, y: 1 },
        { x: 60, y: 0 },
        { x: 61, y: 5 },
        { x: 62, y: 8 },
        { x: 63, y: 3 },
        { x: 64, y: 4 },
        { x: 65, y: 7 },
        { x: 66, y: 2 },
        { x: 67, y: 6 },
        { x: 68, y: 1 },
        { x: 69, y: 9 },
        { x: 70, y: 0 },
        { x: 71, y: 5 },
        { x: 72, y: 8 },
        { x: 73, y: 3 },
        { x: 74, y: 7 },
        { x: 75, y: 4 },
        { x: 76, y: 1 },
        { x: 77, y: 9 },
        { x: 78, y: 6 },
        { x: 79, y: 2 },
        { x: 80, y: 0 },
        { x: 81, y: 5 },
        { x: 82, y: 8 },
        { x: 83, y: 3 },
        { x: 84, y: 7 },
        { x: 85, y: 1 },
        { x: 86, y: 6 },
        { x: 87, y: 2 },
        { x: 88, y: 9 },
        { x: 89, y: 4 },
        { x: 90, y: 0 },
        { x: 91, y: 5 },
        { x: 92, y: 8 },
        { x: 93, y: 3 },
        { x: 94, y: 6 },
        { x: 95, y: 1 },
        { x: 96, y: 4 },
        { x: 97, y: 9 },
        { x: 98, y: 2 },
        { x: 99, y: 7 },
    ];

    //Act -- sort points
    const result = sortPoints(points)

    //Assert -- verify that 100 unsorted points are sorted correctly
    expect(result).toEqual(expected)
})