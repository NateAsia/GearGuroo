//
//  ContentView.swift
//  GearGuRoo
//
//  Created by Nathaniel Asia on 11/22/22.
//

import SwiftUI

var name        = ""
var gearRec     = 1  // Change Based on ESP INPUT
var mph         = 0
var angleR      = 0

var themeA   = Color("LOGO-MATCH")



let rads = 15 // Corner Radii


struct MainView: View {
    var body: some View {
        
        
        TabView {
                ContentView()
                    .tabItem {
                        Label("RIDE", systemImage: "bicycle")
                    }

                SettingsView()
                    .tabItem {
                        Label("SETTINGS", systemImage: "gearshape.2")
                    }
        }
        .accentColor(Color("TABS-COLOR"))
        
        
    }
}

struct ContentView: View {
    var body: some View {
        
        ZStack{
        
        
        
        VStack{
            
            
            Button(action:{}, label:{
                Image("GG-BANNER")
                    .resizable()
                    .aspectRatio(contentMode: .fit)
                    .cornerRadius(CGFloat(rads))
                    .padding(.horizontal)
            })
        
            Text("Keep. Moving. Forward")
                .font(.title2)
        
            Spacer()
        
//            Text("Welcome " + name + ",")
//                .font(.callout)
//
//
//            Spacer()
        
            VStack{
                Text("Recommended Gear")
                    .font(.title)
                    .fontWeight(.black)
                Text(String(gearRec) )
                    .font(.system(size: 60))
                    .fontWeight(.black)
                
            }
            .frame(maxWidth: .infinity)
            .padding()
                .background(themeA)
                .foregroundColor(.white)
                .cornerRadius(15)
                .padding(.horizontal, 20)
            
                
        
            HStack{

                
                VStack{
                    Text("Speed").font(.title).fontWeight(.medium).padding(.bottom, 1)
                    Text(String(mph) + " MPH").font(.title3)
                }.frame(maxWidth: .infinity)
                    .padding(.vertical,30)
                    .background(themeA)
                    .foregroundColor(.white)
                    .shadow(radius:15)
                    .cornerRadius(15)
                    .padding(.leading,20)
                
                
                VStack{
                    Text("Angle").font(.title).fontWeight(.medium).padding(.bottom, 1)
                    Text(String(angleR)).font(.title3)
                }.frame(maxWidth: .infinity)
                    .padding(.vertical, 30)
                    .background(themeA)
                    .foregroundColor(.white)
                    .shadow(radius:15)
                    .cornerRadius(15)
                    .padding(.trailing,20)
                
            }
            .padding(.top)
        
            Spacer()
            Divider().padding()
        
        
            }
        
        }
        
    }
}




struct SettingsView: View {
    
    @State private var numGears    = 6.0
    @State private var Diamater    = 27.0
    @State private var offset      = 0.0
    @State private var diff        = 1.0
    @State private var name        = "NAME"
    
    var body: some View {
        
        
        
        ZStack{
            VStack{
                Button(action:{}, label:{
                    Image("GG-BANNER")
                        .resizable()
                        .aspectRatio(contentMode: .fit)
                        .cornerRadius(CGFloat(rads))
                        .padding(.horizontal)
                })
            
                Text("Keep. Moving. Forward")
                    .font(.title2)
                
                Spacer()
                    settingInput(min: 1, max: 30, icon: "gear", text: "Number of Gears", value: $numGears, color: themeA)
                    settingInput(min: 10, max: 30, icon: "togglepower", text: "Wheel Diameter", value: $Diamater, color: themeA)
//                Spacer()
                settingInput(min: 1, max: 3, icon: "flame.circle", text: "Difficulty", value: $diff, color: themeA)
                Button(action: {}, label: {
                    
                    Text("CALIBRATE ANGLE")
                        .font(.title3)
                        .fontWeight(.bold)
                        .foregroundColor(Color.white)
                        .padding()
                        .frame(maxWidth:.infinity)
                        .background(themeA)
                        .shadow(radius:15)
                        .cornerRadius(CGFloat(rads))
                        .padding(.horizontal, 20)
                    
                })
                
                
                Spacer()
                Divider().padding()
                
                
            }
        }
        
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        Group {
            MainView()
        }
    }
}



