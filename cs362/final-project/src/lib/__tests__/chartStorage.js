/**
 * @jest-environment jsdom
 */

const { saveChart, loadAllSavedCharts, loadSavedChart, updateCurrentChartData, loadCurrentChartData } = require('../chartStorage');

beforeEach(() => {
    localStorage.clear();
});

describe("loadAllSavedCharts()", () => {
    test("returns an empty array when no charts are saved", function () {
        expect(loadAllSavedCharts.apply()).toEqual([]);
    });

    test("returns all saved charts", function () {
        const charts = [{ title: 'Chart A' }, { title: 'Chart B' }];
        localStorage.setItem('savedCharts', JSON.stringify(charts));
        expect(loadAllSavedCharts()).toEqual(charts);
    });
});

describe("saveChart()", () => {
    test("saves a new chart when no charts exist", function () {
        const chart = { title: 'Chart 1' };
        saveChart(chart);
        expect(loadAllSavedCharts()).toEqual([chart]);
    });

    test("appends a new chart when no index is provided", function () {
        const chart1 = { title: 'Chart 1' };
        const chart2 = { title: 'Chart 2' };
        saveChart(chart1);
        saveChart(chart2);
        expect(loadAllSavedCharts()).toEqual([chart1, chart2]);
    });

    test("overwrites an existing chart when a valid index is provided", function () {
        const chart1 = { title: 'Chart 1' };
        const chart2 = { title: 'Chart 2' };
        saveChart(chart1);
        saveChart(chart2, 0);
        expect(loadAllSavedCharts()).toEqual([chart2]);
    });

    test("appends instead of overwriting when index is out of bounds", function () {
        const chart1 = { title: 'Chart 1' };
        const chart2 = { title: 'Chart 2' };
        saveChart(chart1);
        saveChart(chart2, 99);
        expect(loadAllSavedCharts()).toEqual([chart1, chart2]);
    });

    test("appends instead of overwriting when index is null", function () {
        const chart1 = { title: 'Chart 1' };
        const chart2 = { title: 'Chart 2' };
        saveChart(chart1);
        saveChart(chart2, null);
        expect(loadAllSavedCharts()).toEqual([chart1, chart2]);
    });
});

describe("loadSavedChart()", () => {
    test("returns the correct chart at a given index", function () {
        const chart1 = { title: 'Chart 1' };
        const chart2 = { title: 'Chart 2' };
        saveChart(chart1);
        saveChart(chart2);
        expect(loadSavedChart(0)).toEqual(chart1);
        expect(loadSavedChart(1)).toEqual(chart2);
    });

    test("returns empty object when index is out of bounds", function () {
        const chart = { title: 'Chart 1' };
        saveChart(chart);
        expect(loadSavedChart(99)).toEqual({});
    });

    test("returns empty object when no charts are saved", function () {
        expect(loadSavedChart(0)).toEqual({});
    });
});
      
describe("updateCurrentChartData()", () => {
    test("stores data in localStorage", function () {
        const data = { type: 'bar', points: [{ x: 1, y: 2 }] };
        updateCurrentChartData(data);
        const stored = JSON.parse(localStorage.getItem('currentChartData'));
        expect(stored).toEqual(data);
    });

    test("overwrites existing data", function () {
        const data1 = { type: 'line', points: [] };
        const data2 = { type: 'scatter', points: [{ x: 5, y: 10 }] };
        updateCurrentChartData(data1);
        updateCurrentChartData(data2);
        const stored = JSON.parse(localStorage.getItem('currentChartData'));
        expect(stored).toEqual(data2);
    });

    test("stores complex chart data structures", function () {
        const data = { type: 'bar', xLabel: 'X Axis', yLabel: 'Y Axis', points: [{ x: 1, y: 2 }, { x: 3, y: 4 }] };
        updateCurrentChartData(data);
        const stored = JSON.parse(localStorage.getItem('currentChartData'));
        expect(stored).toEqual(data);
    });
});

describe("loadCurrentChartData()", () => {
    test("returns an empty object when no data is stored", function () {
        expect(loadCurrentChartData()).toEqual({});
    });

    test("returns the stored chart data", function () {
        const data = { type: 'line', points: [{ x: 1, y: 2 }] };
        localStorage.setItem('currentChartData', JSON.stringify(data));
        expect(loadCurrentChartData()).toEqual(data);
    });

    test("correctly parses JSON from localStorage", function () {
        const data = { type: 'scatter', xLabel: 'X', yLabel: 'Y', points: [{ x: 0, y: 0 }] };
        localStorage.setItem('currentChartData', JSON.stringify(data));
        expect(loadCurrentChartData()).toEqual(data);
    });
});