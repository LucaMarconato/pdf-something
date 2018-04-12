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
        let c_string: UnsafeMutablePointer<Int8>! = getLastOpenedFile()
        let pdfName = String(cString: c_string)
        freeString(c_string)
        
        label.text = pdfName
        
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

