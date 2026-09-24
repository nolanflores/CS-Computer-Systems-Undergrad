const NUMERALS = [
    [1000, 'M'],
    [100, 'C'],
    [50, 'L'],
    [10, 'X'],
    [5, 'V'],
    [1, 'I'],
];


/**
 * Converts an Arabic number to a Roman numeral string.
 * @param {number} number - An integer between 1 and 3999 (inclusive)
 * @returns {string} The Roman numeral representation
 * @throws {RangeError} If number is outside the valid range
 */
function toRoman(number) {
    if (!Number.isInteger(number) || number < 1 || number > 3999) {
        throw new RangeError(`Input must be an integer between 1 and 3999, got: ${num}`);
    }

    let result = '';
    for (const [value, numeral] of NUMERALS) {
        while (number >= value) {
            result += numeral;
            number -= value;
        }
    }
    return result;
}

module.exports = { toRoman };