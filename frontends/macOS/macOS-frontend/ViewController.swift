//
//  ViewController.swift
//  macOS-frontend
//
//  Created by macbook on 12/04/2018.
//  Copyright © 2018 macbook. All rights reserved.
//

import Cocoa

class ViewController: NSViewController {
    @IBOutlet weak var label: NSTextField!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        let c_string: UnsafeMutablePointer<Int8>! = getLastOpenedFile()
        let pdfName = String(cString: c_string)
        freeString(c_string)
        
        self.label.stringValue = pdfName        
        // Do any additional setup after loading the view.
    }

    override var representedObject: Any? {
        didSet {
        // Update the view, if already loaded.
        }
    }


}

