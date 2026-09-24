const verifyEmail = require('./verifyEmail');

describe('verifyEmail', () => {
    test('returns false for invalid inputs', () => {
        expect(verifyEmail(1234)).toBe(false);
        expect(verifyEmail('')).toBe(false);
        expect(verifyEmail('plainaddress')).toBe(false);
    });

    test('returns false for malformed email addresses', () => {
        expect(verifyEmail('@missingusername.com')).toBe(false);
        expect(verifyEmail('username@.com')).toBe(false);
        expect(verifyEmail('username@com')).toBe(false);
        expect(verifyEmail('username@domain..com')).toBe(false);
    });

    test('returns true for a valid email', () => {
        expect(verifyEmail('username@domain.com')).toBe(true);
    });
});