//
//  ViewController.swift
//  iOS-frontend
//
//  Created by macbook on 12/04/2018.
//  Copyright © 2018 macbook. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    
    @IBOutlet weak var label: UILabel!
    override func viewDidLoad() {
        super.viewDidLoad()
        let path = write(text: "ehi", to: "test", folder: "folder")
        let c_string: UnsafeMutablePointer<Int8>! = getLastOpenedFile((path as NSString).utf8String)
        let pdfName = String(cString: c_string)
        freeString(c_string)
        
        label.text = pdfName
        
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    func write(text: String, to fileNamed: String, folder: String = "SavedFiles") -> String {
        guard let path = NSSearchPathForDirectoriesInDomains(.documentDirectory, .userDomainMask, true).first else { return ""}
        guard let writePath = NSURL(fileURLWithPath: path).appendingPathComponent(folder) else { return ""}
        try? FileManager.default.createDirectory(atPath: writePath.path, withIntermediateDirectories: true)
        let file = writePath.appendingPathComponent(fileNamed + ".txt")
        try? text.write(to: file, atomically: false, encoding: String.Encoding.utf8)
        return file.absoluteString
    }
    
    
}

