// ICountService.aidl
package com.example.kwmp;

// Declare any non-default types here with import statements

interface ICountService {
    int getCurCountNumber();
    /**
     * Demonstrates some basic types that you can use as parameters
     * and return values in AIDL.
     */
    void basicTypes(int anInt, long aLong, boolean aBoolean, float aFloat,
            double aDouble, String aString);
}