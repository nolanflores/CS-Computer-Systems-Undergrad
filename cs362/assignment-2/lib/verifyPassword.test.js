const verifyPassword = require('./verifyPassword');

describe('verifyPassword', () => {
    test('returns pass false for non-string or empty input', () => {
        expect(verifyPassword(undefined)).toEqual({ pass: false });
        expect(verifyPassword(1234)).toEqual({ pass: false });
        expect(verifyPassword('')).toEqual({ pass: false });
    });

    test('passes for a valid password', () => {
        expect(verifyPassword('Abcdef1!').pass).toBe(true);
    });

    test('fails when too short', () => {
        const result = verifyPassword('Ab1!xyz');
        expect(result.pass).toBe(false);
        expect(result.length).toBe(false);
    });

    test('fails when invalid character is present', () => {
        const result = verifyPassword('Abcdef1!?');
        expect(result.pass).toBe(false);
        expect(result.noInvalid).toBe(false);
    });
});