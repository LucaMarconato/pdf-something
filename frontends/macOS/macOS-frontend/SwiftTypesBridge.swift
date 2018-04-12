//
//  SwiftTypesBridge.swift
//  macOS-frontend
//
//  Created by macbook on 12/04/2018.
//  Copyright © 2018 macbook. All rights reserved.
//

import Foundation

func CStringToString(_ cstring: UnsafePointer<UInt8>) -> String {
    return "Converted"
//    var objectTypeLength: UInt = 0
//    let firstElementOfObjectTypeBuffer = UnsafeRawPointer(cityGMLParser.currentObjectType(withLength: &objectTypeLength))
//    let objectTypeData = Data(bytes: firstElementOfObjectTypeBuffer!, count: Int(objectTypeLength)*MemoryLayout<Int8>.size)
//    objects.last!.type = String(data: objectTypeData, encoding: .utf8)!
    
}

