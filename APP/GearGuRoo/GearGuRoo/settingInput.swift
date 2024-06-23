//
//  ColorSlider.swift
//  spinner
//
//  Created by Nathaniel Asia on 6/3/22.
//

import SwiftUI

struct settingInput: View {
    
    var min: Double = 1
    var max: Double = 30
    var icon: String = "circle.fill"
    var text: String = "INPUT NEEDED"
    
    @Binding var value: Double
    var color: Color
    
    
    
    
    var body: some View {
        
        VStack{
            

            Text(text + " – " + String(Int(value)))         // TOP TEXT
                .font(.title3)
                .fontWeight(.bold)
                .foregroundColor(.white)
                .padding(.top,10)
            
                        
            HStack{                                         // LOWER Slider
                
                Image(systemName: icon)
                    .foregroundColor(.white)
                    .padding(.leading, 7)
                Slider(value: $value, in: min...max, step: 1)
                    .accentColor(.white)
                    .padding(.trailing, 7)
                
            }
                .padding(.bottom, 10)
            
            
        }
            .background(color)
            .cornerRadius(15)
            .shadow(radius:15)
            .padding(.horizontal, 20)
    }
}

struct ColorSlider_Previews: PreviewProvider {
    
    @State static var value = 3.0
    
    static var previews: some View {
        settingInput(value: $value, color: Color.blue)
    }
}
