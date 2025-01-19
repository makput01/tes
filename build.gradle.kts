@file:Suppress("UnstableApiUsage")

plugins {
  alias(libs.plugins.android.application) apply false
  alias(libs.plugins.android.library) apply false
  alias(libs.plugins.kotlin.jvm) apply false
  alias(libs.plugins.kotlin.android) apply false
}

buildscript {
  dependencies {
    classpath(libs.kotlin.gradle.plugin)
  }
}

project.group = BuildConfig.packageName
