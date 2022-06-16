package com.tencent.marsMulti.sample.suite;

import com.tencent.marsMulti.sample.MarsServiceProxyTest;

import org.junit.runner.RunWith;
import org.junit.runners.Suite;

/**
 * Runs all unit tests.
 * <p></p>
 * Created by zhaoyuan on 2017/3/21.
 */
@RunWith(Suite.class)
@Suite.SuiteClasses({MarsServiceProxyTest.class})
public class UnitTestSuite {
}
