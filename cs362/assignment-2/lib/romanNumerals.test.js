const { toRoman } = require('./romanNumerals');

describe('toRoman', () => {
    test('converts 1 to I', () => {
        expect(toRoman(1)).toBe('I');
    });
    test('converts 2 to II', () => {
        expect(toRoman(2)).toBe('II');
    });
    test('converts 3 to III', () => {
        expect(toRoman(3)).toBe('III');
    });
    test('converts 5 to V', () => {
        expect(toRoman(5)).toBe('V');
    });
    test('converts 6 to VI', () => {
        expect(toRoman(6)).toBe('VI');
    });
    test('converts 9 to VIIII', () => {
        expect(toRoman(9)).toBe('VIIII');
    });
    test('converts 10 to X', () => {
        expect(toRoman(10)).toBe('X');
    });
    test('converts 40 to XXXX', () => {
        expect(toRoman(40)).toBe('XXXX');
    });
    test('converts 50 to L', () => {
        expect(toRoman(50)).toBe('L');
    });
    test('converts 100 to C', () => {
        expect(toRoman(100)).toBe('C');
    });
    test('converts 1000 to M', () => {
        expect(toRoman(1000)).toBe('M');
    });
    test('converts 2026 to MMXXVI', () => {
        expect(toRoman(2026)).toBe('MMXXVI');
    });
    

    test('throws on 0', () => {
        expect(() => toRoman(0)).toThrow();
    });
    test('throws on 4000', () => {
        expect(() => toRoman(4000)).toThrow();
    });
    test('throws on negative numbers', () => {
        expect(() => toRoman(-1)).toThrow();
    });
});