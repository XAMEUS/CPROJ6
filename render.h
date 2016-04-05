#ifndef __RENDER_H__
#define __RENDER_H__


#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL_opengl.h>
#include "parse.h"
#include "display.h"

//https://en.wikipedia.org/wiki/List_of_colors:_A%E2%80%93F

#define AbsoluteZero glColor3f(0.0,0.28,0.73)
#define Acajou	glColor3f(0.30,0.18,0.15)
#define Acidgreen	glColor3f(0.69,0.75,0.10)
#define Aero	glColor3f(0.49,0.73,0.91)
#define Aeroblue	glColor3f(0.79,0.100,0.90)
#define Africanviolet	glColor3f(0.70,0.52,0.75)
#define AirForceblueRAF	glColor3f(0.36,0.54,0.66)
#define AirForceblueUSAF	glColor3f(0.0,0.19,0.56)
#define Airsuperiorityblue	glColor3f(0.45,0.63,0.76)
#define Alabamacrimson	glColor3f(0.69,0.0,0.16)
#define Aliceblue	glColor3f(0.94,0.97,0.100)
#define AlienArmpit	glColor3f(0.52,0.87,0.1)
#define Alizarincrimson	glColor3f(0.89,0.15,0.21)
#define Alloyorange	glColor3f(0.77,0.38,0.6)
#define Almond	glColor3f(0.94,0.87,0.80)
#define Amaranth	glColor3f(0.90,0.17,0.31)
#define Amaranthdeeppurple	glColor3f(0.62,0.17,0.41)
#define Amaranthpink	glColor3f(0.95,0.61,0.73)
#define Amaranthpurple	glColor3f(0.67,0.15,0.31)
#define Amaranthred	glColor3f(0.83,0.13,0.18)
#define Amazon	glColor3f(0.23,0.48,0.34)
#define Amber	glColor3f(0.100,0.75,0.0)
#define AmberSAEECE	glColor3f(0.100,0.49,0.0)
#define Americanrose	glColor3f(0.100,0.1,0.24)
#define Amethyst	glColor3f(0.60,0.40,0.80)
#define Androidgreen	glColor3f(0.64,0.78,0.22)
#define Antiflashwhite	glColor3f(0.95,0.95,0.96)
#define Antiquebrass	glColor3f(0.80,0.58,0.46)
#define Antiquebronze	glColor3f(0.40,0.36,0.12)
#define Antiquefuchsia	glColor3f(0.57,0.36,0.51)
#define Antiqueruby	glColor3f(0.52,0.11,0.18)
#define Antiquewhite	glColor3f(0.98,0.92,0.84)
#define AoEnglish	glColor3f(0.0,0.50,0.0)
#define Applegreen	glColor3f(0.55,0.71,0.0)
#define Apricot	glColor3f(0.98,0.81,0.69)
#define Aqua	glColor3f(0.0,0.100,0.100)
#define Aquamarine	glColor3f(0.50,0.100,0.83)
#define Arcticlime	glColor3f(0.82,0.100,0.8)
#define Armygreen	glColor3f(0.29,0.33,0.13)
#define Arsenic	glColor3f(0.23,0.27,0.29)
#define Artichoke	glColor3f(0.56,0.59,0.47)
#define Arylideyellow	glColor3f(0.91,0.84,0.42)
#define Ashgrey	glColor3f(0.70,0.75,0.71)
#define Asparagus	glColor3f(0.53,0.66,0.42)
#define Atomictangerine	glColor3f(0.100,0.60,0.40)
#define Auburn	glColor3f(0.65,0.16,0.16)
#define Aureolin	glColor3f(0.99,0.93,0.0)
#define AuroMetalSaurus	glColor3f(0.43,0.50,0.50)
#define Avocado	glColor3f(0.34,0.51,0.1)
#define AztecGold	glColor3f(0.76,0.60,0.33)
#define Azure	glColor3f(0.0,0.50,0.100)
#define Azurewebcolor	glColor3f(0.94,0.100,0.100)
#define Azuremist	glColor3f(0.94,0.100,0.100)
#define Azureishwhite	glColor3f(0.86,0.91,0.96)
#define Bdazzledblue	glColor3f(0.18,0.35,0.58)
#define Babyblue	glColor3f(0.54,0.81,0.94)
#define Babyblueeyes	glColor3f(0.63,0.79,0.95)
#define Babypink	glColor3f(0.96,0.76,0.76)
#define Babypowder	glColor3f(0.100,0.100,0.98)
#define BakerMillerpink	glColor3f(0.100,0.57,0.69)
#define Ballblue	glColor3f(0.13,0.67,0.80)
#define BananaMania	glColor3f(0.98,0.91,0.71)
#define Bananayellow	glColor3f(0.100,0.88,0.21)
#define Bangladeshgreen	glColor3f(0.0,0.42,0.31)
#define Barbiepink	glColor3f(0.88,0.13,0.54)
#define Barnred	glColor3f(0.49,0.4,0.1)
#define BatteryChargedBlue	glColor3f(0.11,0.67,0.84)
#define Battleshipgrey	glColor3f(0.52,0.52,0.51)
#define Bazaar	glColor3f(0.60,0.47,0.48)
#define Beaublue	glColor3f(0.74,0.83,0.90)
#define Beaver	glColor3f(0.62,0.51,0.44)
#define Begonia	glColor3f(0.98,0.43,0.47)
#define Beige	glColor3f(0.96,0.96,0.86)
#define Bigdiporuby	glColor3f(0.61,0.15,0.26)
#define BigFootFeet	glColor3f(0.91,0.56,0.35)
#define Bisque	glColor3f(0.100,0.89,0.77)
#define Bistre	glColor3f(0.24,0.17,0.12)
#define Bistrebrown	glColor3f(0.59,0.44,0.9)
#define Bitterlemon	glColor3f(0.79,0.88,0.5)
#define Bitterlime	glColor3f(0.75,0.100,0.0)
#define Bittersweet	glColor3f(0.100,0.44,0.37)
#define Bittersweetshimmer	glColor3f(0.75,0.31,0.32)
#define Black	glColor3f(0.0,0.0,0.0)
#define Blackbean	glColor3f(0.24,0.5,0.1)
#define BlackCoral	glColor3f(0.33,0.38,0.44)
#define Blackleatherjacket	glColor3f(0.15,0.21,0.16)
#define Blackolive	glColor3f(0.23,0.24,0.21)
#define BlackShadows	glColor3f(0.75,0.69,0.70)
#define Blanchedalmond	glColor3f(0.100,0.92,0.80)
#define Blastoffbronze	glColor3f(0.65,0.44,0.39)
#define BleudeFrance	glColor3f(0.19,0.55,0.91)
#define BlizzardBlue	glColor3f(0.67,0.90,0.93)
#define Blond	glColor3f(0.98,0.94,05)
#define Blue	glColor3f(0.0,0.0,0.100)
#define BlueCrayola	glColor3f(0.12,0.46,0.100)
#define BlueMunsell	glColor3f(0.0,0.58,0.69)
#define BlueNCS	glColor3f(0.0,0.53,0.74)
#define BluePantone	glColor3f(0.0,0.9,0.66)
#define Bluepigment	glColor3f(0.20,0.20,0.60)
#define BlueRYB	glColor3f(0.1,0.28,0.100)
#define BlueBell	glColor3f(0.64,0.64,0.82)
#define BlueBolt	glColor3f(0.0,0.73,0.98)
#define BlueJeans	glColor3f(0.36,0.68,0.93)
#define BlueLagoon	glColor3f(0.67,0.90,0.93)
#define Bluesapphire	glColor3f(0.7,0.38,0.50)
#define Blueyonder	glColor3f(0.31,0.45,0.65)
#define Bluegray	glColor3f(0.40,0.60,0.80)
#define Bluegreen	glColor3f(0.5,0.60,0.73)
#define Bluemagentaviolet	glColor3f(0.33,0.21,0.57)
#define Blueviolet	glColor3f(0.54,0.17,0.89)
#define Blueberry	glColor3f(0.31,0.53,0.97)
#define Bluebonnet	glColor3f(0.11,0.11,0.94)
#define Blush	glColor3f(0.87,0.36,0.51)
#define Bole	glColor3f(0.47,0.27,0.23)
#define Bondiblue	glColor3f(0.0,0.58,0.71)
#define Bone	glColor3f(0.89,0.85,0.79)
#define BoogerBuster	glColor3f(0.87,0.89,0.42)
#define BostonUniversityRed	glColor3f(0.80,0.0,0.0)
#define Bottlegreen	glColor3f(0.0,0.42,0.31)
#define Boysenberry	glColor3f(0.53,0.20,0.38)
#define Brandeisblue	glColor3f(0.0,0.44,0.100)
#define Brass	glColor3f(0.71,0.65,0.26)
#define Brickred	glColor3f(0.80,0.25,0.33)
#define Brightcerulean	glColor3f(0.11,0.67,0.84)
#define Brightgreen	glColor3f(0.40,0.100,0.0)
#define Brightlavender	glColor3f(0.75,0.58,0.89)
#define Brightlilac	glColor3f(0.85,0.57,0.94)
#define Brightmaroon	glColor3f(0.76,0.13,0.28)
#define Brightnavyblue	glColor3f(0.10,0.45,0.82)
#define Brightpink	glColor3f(0.100,0.0,0.50)
#define Brightturquoise	glColor3f(0.3,0.91,0.87)
#define Brightube	glColor3f(0.82,0.62,0.91)
#define BrightYellowCrayola	glColor3f(0.100,0.67,0.11)
#define Brilliantazure	glColor3f(0.20,0.60,0.100)
#define Brilliantlavender	glColor3f(0.96,0.73,0.100)
#define Brilliantrose	glColor3f(0.100,0.33,0.64)
#define Brinkpink	glColor3f(0.98,0.38,0.50)
#define Britishracinggreen	glColor3f(0.0,0.26,0.15)
#define Bronze	glColor3f(0.80,0.50,0.20)
#define BronzeYellow	glColor3f(0.45,0.44,0.0)
#define Browntraditional	glColor3f(0.59,0.29,0.0)
#define Brownweb	glColor3f(0.65,0.16,0.16)
#define BrownSugar	glColor3f(0.69,0.43,0.30)
#define BrownYellow	glColor3f(0.80,0.60,0.40)
#define Brownnose	glColor3f(0.42,0.27,0.14)
#define Brunswickgreen	glColor3f(0.11,0.30,0.24)
#define Bubblegum	glColor3f(0.100,0.76,0.80)
#define Bubbles	glColor3f(0.91,0.100,0.100)
#define Budgreen	glColor3f(0.48,0.71,0.38)
#define Buff	glColor3f(0.94,0.86,0.51)
#define Bulgarianrose	glColor3f(0.28,0.2,0.3)
#define Burgundy	glColor3f(0.50,0.0,0.13)
#define Burlywood	glColor3f(0.87,0.72,0.53)
#define BurnishedBrown	glColor3f(0.63,0.48,0.45)
#define Burntorange	glColor3f(0.80,0.33,0.0)
#define Burntsienna	glColor3f(0.91,0.45,0.32)
#define Burntumber	glColor3f(0.54,0.20,0.14)
#define Byzantine	glColor3f(0.74,0.20,0.64)
#define Byzantium	glColor3f(0.44,0.16,0.39)
#define Cadet	glColor3f(0.33,0.41,0.45)
#define Cadetblue	glColor3f(0.37,0.62,0.63)
#define Cadetgrey	glColor3f(0.57,0.64,0.69)
#define Cadmiumgreen	glColor3f(0.0,0.42,0.24)
#define Cadmiumorange	glColor3f(0.93,0.53,0.18)
#define Cadmiumred	glColor3f(0.89,0.0,0.13)
#define Cadmiumyellow	glColor3f(0.100,0.96,0.0)
#define Cafeaulait	glColor3f(0.65,0.48,0.36)
#define Cafenoir	glColor3f(0.29,0.21,0.13)
#define CalPolygreen	glColor3f(0.12,0.30,0.17)
#define CambridgeBlue	glColor3f(0.64,0.76,0.68)
#define Camel	glColor3f(0.76,0.60,0.42)
#define Cameopink	glColor3f(0.94,0.73,0.80)
#define Camouflagegreen	glColor3f(0.47,0.53,0.42)
#define Canary	glColor3f(0.100,0.100,0.60)
#define Canaryyellow	glColor3f(0.100,0.94,0.0)
#define Candyapplered	glColor3f(0.100,0.3,0.0)
#define Candypink	glColor3f(0.89,0.44,0.48)
#define Capri	glColor3f(0.0,0.75,0.100)
#define Caputmortuum	glColor3f(0.35,0.15,0.13)
#define Cardinal	glColor3f(0.77,0.12,0.23)
#define Caribbeangreen	glColor3f(0.0,0.80,0.60)
#define Carmine	glColor3f(0.59,0.0,0.9)
#define CarmineMP	glColor3f(0.84,0.0,0.25)
#define Carminepink	glColor3f(0.92,0.30,0.26)
#define Carminered	glColor3f(0.100,0.0,0.22)
#define Carnationpink	glColor3f(0.100,0.65,0.79)
#define Carnelian	glColor3f(0.70,0.11,0.11)
#define Carolinablue	glColor3f(0.34,0.63,0.83)
#define Carrotorange	glColor3f(0.93,0.57,0.13)
#define Castletongreen	glColor3f(0.0,0.34,0.25)
#define Catalinablue	glColor3f(0.2,0.16,0.47)
#define Catawba	glColor3f(0.44,0.21,0.26)
#define CedarChest	glColor3f(0.79,0.35,0.29)
#define Ceil	glColor3f(0.57,0.63,0.81)
#define Celadon	glColor3f(0.67,0.88,0.69)
#define Celadonblue	glColor3f(0.0,0.48,0.65)
#define Celadongreen	glColor3f(0.18,0.52,0.49)
#define Celeste	glColor3f(0.70,0.100,0.100)
#define Celestialblue	glColor3f(0.29,0.59,0.82)
#define Cerise	glColor3f(0.87,0.19,0.39)
#define Cerisepink	glColor3f(0.93,0.23,0.51)
#define Cerulean	glColor3f(0.0,0.48,0.65)
#define Ceruleanblue	glColor3f(0.16,0.32,0.75)
#define Ceruleanfrost	glColor3f(0.43,0.61,0.76)
#define CGBlue	glColor3f(0.0,0.48,0.65)
#define CGRed	glColor3f(0.88,0.24,0.19)
#define Chamoisee	glColor3f(0.63,0.47,0.35)
#define Champagne	glColor3f(0.97,0.91,0.81)
#define Champagnepink	glColor3f(0.95,0.87,0.81)
#define Charcoal	glColor3f(0.21,0.27,0.31)
#define Charlestongreen	glColor3f(0.14,0.17,0.17)
#define Charmpink	glColor3f(0.90,0.56,0.67)
#define Chartreusetraditional	glColor3f(0.87,0.100,0.0)
#define Chartreuseweb	glColor3f(0.50,0.100,0.0)
#define Cherry	glColor3f(0.87,0.19,0.39)
#define Cherryblossompink	glColor3f(0.100,0.72,0.77)
#define Chestnut	glColor3f(0.58,0.27,0.21)
#define Chinapink	glColor3f(0.87,0.44,0.63)
#define Chinarose	glColor3f(0.66,0.32,0.43)
#define Chinesered	glColor3f(0.67,0.22,0.12)
#define Chineseviolet	glColor3f(0.52,0.38,0.53)
#define Chlorophyllgreen	glColor3f(0.29,0.100,0.0)
#define Chocolatetraditional	glColor3f(0.48,0.25,0.0)
#define Chocolateweb	glColor3f(0.82,0.41,0.12)
#define Chromeyellow	glColor3f(0.100,0.65,0.0)
#define Cinereous	glColor3f(0.60,0.51,0.48)
#define Cinnabar	glColor3f(0.89,0.26,0.20)
#define Daffodil	glColor3f(0.100,0.100,0.19)
#define CinnamonSatin	glColor3f(0.80,0.38,0.49)

#define Cinnamoncitationneeded	glColor3f(0.82,0.41,0.12)

#define Citrine	glColor3f(0.89,0.82,0.4)

#define Citron	glColor3f(0.62,0.66,0.12)

#define Claret	glColor3f(0.50,0.9,0.20)

#define Classicrose	glColor3f(0.98,0.80,0.91)

#define CobaltBlue	glColor3f(0.0,0.28,0.67)

#define Cocoabrown	glColor3f(0.82,0.41,0.12)

#define Coconut	glColor3f(0.59,0.35,0.24)

#define Coffee	glColor3f(0.44,0.31,0.22)

#define ColumbiaBlue	glColor3f(0.77,0.85,0.89)

#define Congopink	glColor3f(0.97,0.51,0.47)

#define CoolBlack	glColor3f(0.0,0.18,0.39)

#define Coolgrey	glColor3f(0.55,0.57,0.67)

#define Copper	glColor3f(0.72,0.45,0.20)

#define CopperCrayola	glColor3f(0.85,0.54,0.40)

#define Copperpenny	glColor3f(0.68,0.44,0.41)

#define Copperred	glColor3f(0.80,0.43,0.32)

#define Copperrose	glColor3f(0.60,0.40,0.40)

#define Coquelicot	glColor3f(0.100,0.22,0.0)

#define Coral	glColor3f(0.100,0.50,0.31)

#define Coralpink	glColor3f(0.97,0.51,0.47)

#define Coralred	glColor3f(0.100,0.25,0.25)

#define CoralReef	glColor3f(0.99,0.49,0.43)

#define Cordovan	glColor3f(0.54,0.25,0.27)

#define Corn	glColor3f(0.98,0.93,0.36)

#define CornellRed	glColor3f(0.70,0.11,0.11)

#define Cornflowerblue	glColor3f(0.39,0.58,0.93)

#define Cornsilk	glColor3f(0.100,0.97,0.86)

#define CosmicCobalt	glColor3f(0.18,0.18,0.53)

#define Cosmiclatte	glColor3f(0.100,0.97,0.91)

#define Cottoncandy	glColor3f(0.100,0.74,0.85)

#define Coyotebrown	glColor3f(0.51,0.38,0.24)

#define Cream	glColor3f(0.100,0.99,0.82)

#define Crimson	glColor3f(0.86,0.8,0.24)

#define Crimsonglory	glColor3f(0.75,0.0,0.20)

#define Crimsonred	glColor3f(0.60,0.0,0.0)

#define Cultured	glColor3f(0.96,0.96,0.96)

#define Cyan	glColor3f(0.0,0.100,0.100)

#define Cyanprocess	glColor3f(0.0,0.72,0.92)

#define Cyanazure	glColor3f(0.31,0.51,0.71)

#define Cyancobaltblue	glColor3f(0.16,0.35,0.61)

#define Cyancornflowerblue	glColor3f(0.29,0.55,0.76)

#define Cyanblueazure	glColor3f(0.27,0.51,0.75)

#define Cybergrape	glColor3f(0.35,0.26,0.49)

#define Cyberyellow	glColor3f(0.100,0.83,0.0)

#define Cyclamen	glColor3f(0.96,0.44,0.63)


#define Dandelion	glColor3f(0.94,0.88,0.19)

#define Darkblue	glColor3f(0.0,0.0,0.55)

#define Darkbluegray	glColor3f(0.40,0.40,0.60)

#define Darkbrown	glColor3f(0.40,0.26,0.13)

#define Darkbrowntangelo	glColor3f(0.53,0.40,0.31)

#define Darkbyzantium	glColor3f(0.36,0.22,0.33)

#define Darkcandyapplered	glColor3f(0.64,0.0,0.0)

#define Darkcerulean	glColor3f(0.3,0.27,0.49)

#define Darkchestnut	glColor3f(0.60,0.41,0.38)

#define Darkcoral	glColor3f(0.80,0.36,0.27)

#define Darkcyan	glColor3f(0.0,0.55,0.55)

#define Darkelectricblue	glColor3f(0.33,0.41,0.47)

#define Darkgoldenrod	glColor3f(0.72,0.53,0.4)

#define DarkgrayX11	glColor3f(0.66,0.66,0.66)

#define Darkgreen	glColor3f(0.0,0.20,0.13)

#define DarkgreenX11	glColor3f(0.0,0.39,0.0)

#define Darkgunmetal	glColor3f(0.12,0.15,0.16)

#define Darkimperialblue	glColor3f(0.0,0.8,0.49)

#define Darkjunglegreen	glColor3f(0.10,0.14,0.13)

#define Darkkhaki	glColor3f(0.74,0.72,0.42)

#define Darklava	glColor3f(0.28,0.24,0.20)

#define Darklavender	glColor3f(0.45,0.31,0.59)

#define Darkliver	glColor3f(0.33,0.29,0.31)

#define Darkliverhorses	glColor3f(0.33,0.24,0.22)

#define Darkmagenta	glColor3f(0.55,0.0,0.55)

#define Darkmediumgray	glColor3f(0.66,0.66,0.66)

#define Darkmidnightblue	glColor3f(0.0,0.20,0.40)

#define Darkmossgreen	glColor3f(0.29,0.36,0.14)

#define Darkolivegreen	glColor3f(0.33,0.42,0.18)

#define Darkorange	glColor3f(0.100,0.55,0.0)

#define Darkorchid	glColor3f(0.60,0.20,0.80)

#define Darkpastelblue	glColor3f(0.47,0.62,0.80)

#define Darkpastelgreen	glColor3f(0.1,0.75,0.24)

#define Darkpastelpurple	glColor3f(0.59,0.44,0.84)

#define Darkpastelred	glColor3f(0.76,0.23,0.13)

#define Darkpink	glColor3f(0.91,0.33,0.50)

#define Darkpowderblue	glColor3f(0.0,0.20,0.60)

#define Darkpuce	glColor3f(0.31,0.23,0.24)

#define Darkpurple	glColor3f(0.19,0.10,0.20)

#define Darkraspberry	glColor3f(0.53,0.15,0.34)

#define Darkred	glColor3f(0.55,0.0,0.0)

#define Darksalmon	glColor3f(0.91,0.59,0.48)

#define Darkscarlet	glColor3f(0.34,0.1,0.10)

#define Darkseagreen	glColor3f(0.56,0.74,0.56)

#define Darksienna	glColor3f(0.24,0.8,0.8)

#define Darkskyblue	glColor3f(0.55,0.75,0.84)

#define Darkslateblue	glColor3f(0.28,0.24,0.55)

#define Darkslategray	glColor3f(0.18,0.31,0.31)

#define Darkspringgreen	glColor3f(0.9,0.45,0.27)

#define Darktan	glColor3f(0.57,0.51,0.32)

#define Darktangerine	glColor3f(0.100,0.66,0.7)

#define Darktaupe	glColor3f(0.28,0.24,0.20)

#define Darkterracotta	glColor3f(0.80,0.31,0.36)

#define Darkturquoise	glColor3f(0.0,0.81,0.82)

#define Darkvanilla	glColor3f(0.82,0.75,0.66)

#define Darkviolet	glColor3f(0.58,0.0,0.83)

#define Darkyellow	glColor3f(0.61,0.53,0.5)

#define Dartmouthgreen	glColor3f(0.0,0.44,0.24)

#define Davysgrey	glColor3f(0.33,0.33,0.33)

#define Debianred	glColor3f(0.84,0.4,0.33)

#define Deepaquamarine	glColor3f(0.25,0.51,0.43)

#define Deepcarmine	glColor3f(0.66,0.13,0.24)

#define Deepcarminepink	glColor3f(0.94,0.19,0.22)

#define Deepcarrotorange	glColor3f(0.91,0.41,0.17)

#define Deepcerise	glColor3f(0.85,0.20,0.53)

#define Deepchampagne	glColor3f(0.98,0.84,0.65)

#define Deepchestnut	glColor3f(0.73,0.31,0.28)

#define Deepcoffee	glColor3f(0.44,0.26,0.25)

#define Deepfuchsia	glColor3f(0.76,0.33,0.76)

#define DeepGreen	glColor3f(0.2,0.40,0.3)

#define Deepgreencyanturquoise	glColor3f(0.5,0.49,0.38)

#define Deepjunglegreen	glColor3f(0.0,0.29,0.29)

#define Deepkoamaru	glColor3f(0.20,0.20,0.40)

#define Deeplemon	glColor3f(0.96,0.78,0.10)

#define Deeplilac	glColor3f(0.60,0.33,0.73)

#define Deepmagenta	glColor3f(0.80,0.0,0.80)

#define Deepmaroon	glColor3f(0.51,0.0,0.0)

#define Deepmauve	glColor3f(0.83,0.45,0.83)

#define Deepmossgreen	glColor3f(0.21,0.37,0.23)

#define Deeppeach	glColor3f(0.100,0.80,0.64)

#define Deeppink	glColor3f(0.100,0.8,0.58)

#define Deeppuce	glColor3f(0.66,0.36,0.41)

#define DeepRed	glColor3f(0.52,0.0,0.0)

#define Deepruby	glColor3f(0.52,0.25,0.36)

#define Deepsaffron	glColor3f(0.100,0.60,0.20)

#define Deepskyblue	glColor3f(0.0,0.75,0.100)

#define DeepSpaceSparkle	glColor3f(0.29,0.39,0.42)

#define Deepspringbud	glColor3f(0.33,0.42,0.18)

#define DeepTaupe	glColor3f(0.49,0.37,0.38)

#define DeepTuscanred	glColor3f(0.40,0.26,0.30)

#define Deepviolet	glColor3f(0.20,0.0,0.40)

#define Deer	glColor3f(0.73,0.53,0.35)

#define Denim	glColor3f(0.8,0.38,0.74)

#define DenimBlue	glColor3f(0.13,0.26,0.71)

#define Desaturatedcyan	glColor3f(0.40,0.60,0.60)

#define Desert	glColor3f(0.76,0.60,0.42)

#define Desertsand	glColor3f(0.93,0.79,0.69)

#define Desire	glColor3f(0.92,0.24,0.33)

#define Diamond	glColor3f(0.73,0.95,0.100)

#define Dimgray	glColor3f(0.41,0.41,0.41)

#define DingyDungeon	glColor3f(0.77,0.19,0.32)

#define Dirt	glColor3f(0.61,0.46,0.33)

#define Dodgerblue	glColor3f(0.12,0.56,0.100)

#define Dogwoodrose	glColor3f(0.84,0.9,0.41)

#define Dollarbill	glColor3f(0.52,0.73,0.40)

#define DolphinGray	glColor3f(0.51,0.56,0.52)

#define Donkeybrown	glColor3f(0.40,0.30,0.16)

#define Drab	glColor3f(0.59,0.44,0.9)

#define Dukeblue	glColor3f(0.0,0.0,0.61)

#define Duststorm	glColor3f(0.90,0.80,0.79)

#define Dutchwhite	glColor3f(0.94,0.87,0.73)

#define Earthyellow	glColor3f(0.88,0.66,0.37)

#define Ebony	glColor3f(0.33,0.36,0.31)

#define Ecru	glColor3f(0.76,0.70,0.50)

#define Eerieblack	glColor3f(0.11,0.11,0.11)

#define Eggplant	glColor3f(0.38,0.25,0.32)

#define Eggshell	glColor3f(0.94,0.92,0.84)

#define Egyptianblue	glColor3f(0.6,0.20,0.65)

#define Electricblue	glColor3f(0.49,0.98,0.100)

#define Electriccrimson	glColor3f(0.100,0.0,0.25)

#define Electriccyan	glColor3f(0.0,0.100,0.100)

#define Electricgreen	glColor3f(0.0,0.100,0.0)

#define Electricindigo	glColor3f(0.44,0.0,0.100)

#define Electriclavender	glColor3f(0.96,0.73,0.100)

#define Electriclime	glColor3f(0.80,0.100,0.0)

#define Electricpurple	glColor3f(0.75,0.0,0.100)

#define Electricultramarine	glColor3f(0.25,0.0,0.100)

#define Electricviolet	glColor3f(0.56,0.0,0.100)

#define Electricyellow	glColor3f(0.100,0.100,0.20)

#define Emerald	glColor3f(0.31,0.78,0.47)

#define Eminence	glColor3f(0.42,0.19,0.51)

#define Englishgreen	glColor3f(0.11,0.30,0.24)

#define Englishlavender	glColor3f(0.71,0.51,0.58)

#define Englishred	glColor3f(0.67,0.29,0.32)

#define Englishvermillion	glColor3f(0.80,0.28,0.29)

#define Englishviolet	glColor3f(0.34,0.24,0.36)

#define Etonblue	glColor3f(0.59,0.78,0.64)

#define Eucalyptus	glColor3f(0.27,0.84,0.66)

#define Fallow	glColor3f(0.76,0.60,0.42)

#define Falured	glColor3f(0.50,0.9,0.9)

#define Fandango	glColor3f(0.71,0.20,0.54)

#define Fandangopink	glColor3f(0.87,0.32,0.52)

#define Fashionfuchsia	glColor3f(0.96,0.0,0.63)

#define Fawn	glColor3f(0.90,0.67,0.44)

#define Feldgrau	glColor3f(0.30,0.36,0.33)

#define Feldspar	glColor3f(0.99,0.84,0.69)

#define Ferngreen	glColor3f(0.31,0.47,0.26)

#define FerrariRed	glColor3f(0.100,0.16,0.0)

#define Fielddrab	glColor3f(0.42,0.33,0.12)

#define FieryRose	glColor3f(0.100,0.33,0.44)

#define Fireenginered	glColor3f(0.81,0.13,0.16)

#define Firebrick	glColor3f(0.70,0.13,0.13)

#define Flame	glColor3f(0.89,0.35,0.13)

#define Flamingopink	glColor3f(0.99,0.56,0.67)

#define Flattery	glColor3f(0.42,0.27,0.14)

#define Flavescent	glColor3f(0.97,0.91,0.56)

#define Flax	glColor3f(0.93,0.86,0.51)

#define Flirt	glColor3f(0.64,0.0,0.43)

#define Floralwhite glColor3f(0.100,0.98,0.94)

#define Fluorescentorange	glColor3f(0.100,0.75,0.0)

#define Fluorescentpink	glColor3f(0.100,0.8,0.58)

#define Fluorescentyellow	glColor3f(0.80,0.100,0.0)

#define Folly	glColor3f(0.100,0.0,0.31)

#define Forestgreentraditional	glColor3f(0.0,0.27,0.13)

#define Forestgreenweb	glColor3f(0.13,0.55,0.13)

#define Frenchbeige	glColor3f(0.65,0.48,0.36)

#define Frenchbistre	glColor3f(0.52,0.43,0.30)

#define Frenchblue	glColor3f(0.0,0.45,0.73)

#define Frenchfuchsia	glColor3f(0.99,0.25,0.57)

#define Frenchlilac	glColor3f(0.53,0.38,0.56)

#define Frenchlime	glColor3f(0.62,0.99,0.22)

#define Frenchmauve	glColor3f(0.83,0.45,0.83)

#define Frenchpink	glColor3f(0.99,0.42,0.62)

#define Frenchplum	glColor3f(0.51,0.8,0.33)

#define Frenchpuce	glColor3f(0.31,0.9,0.4)

#define Frenchraspberry	glColor3f(0.78,0.17,0.28)

#define Frenchrose	glColor3f(0.96,0.29,0.54)

#define Frenchskyblue	glColor3f(0.47,0.71,0.100)

#define Frenchviolet	glColor3f(0.53,0.2,0.81)

#define Frenchwine	glColor3f(0.67,0.12,0.27)

#define FreshAir	glColor3f(0.65,0.91,0.100)

#define Frostbite	glColor3f(0.91,0.21,0.65)

#define Fuchsia	glColor3f(0.100,0.0,0.100)

#define FuchsiaCrayola	glColor3f(0.76,0.33,0.76)

#define Fuchsiapink	glColor3f(0.100,0.47,0.100)

#define Fuchsiapurple	glColor3f(0.80,0.22,0.48)

#define Fuchsiarose	glColor3f(0.78,0.26,0.46)

#define Fulvous	glColor3f(0.89,0.52,0.0)

#define FuzzyWuzzy	glColor3f(0.80,0.40,0.40)

#define white glColor3f(1.0f,1.0f,1.0f)

#define HIGHWAY_MOTORWAY_COLOR Cyclamen
#define HIGHWAY_TRUNK_COLOR Atomictangerine
#define HIGHWAY_PRIMARY_COLOR Deeppeach
#define HIGHWAY_SECONDARY_COLOR Flavescent
#define HIGHWAY_TERTIARY_COLOR white
#define HIGHWAY_UNCLASSIFIED_COLOR white
#define HIGHWAY_RESIDENTIAL_COLOR white
#define HIGHWAY_SERVICE_COLOR white
#define HIGHWAY_MOTORWAY_LINK_COLOR Cyclamen
#define HIGHWAY_TRUNK_LINK_COLOR Atomictangerine
#define HIGHWAY_PRIMARY_LINK_COLOR Deeppeach
#define HIGHWAY_SECONDARY_LINK_COLOR Flavescent
#define HIGHWAY_TERTIARY_LINK_COLOR white
#define HIGHWAY_LIVING_STREET_COLOR Azureishwhite
#define HIGHWAY_PEDESTRIAN_COLOR Darkmediumgray
#define HIGHWAY_TRACK_COLOR AztecGold
#define HIGHWAY_BUS_GUIDEWAY_COLOR AirForceblueRAF
#define HIGHWAY_RACEWAY_COLOR Amaranthpink
#define HIGHWAY_ROAD_COLOR Darkmediumgray
#define HIGHWAY_FOOTWAY_COLOR Begonia
#define HIGHWAY_BRIDLEWAY_COLOR Bottlegreen
#define HIGHWAY_STEPS_COLOR Begonia
#define HIGHWAY_PATH_COLOR Begonia
#define HIGHWAY_CYCLEWAY_COLOR Ceruleanblue
#define HIGHWAY_PROPOSED_COLOR Celestialblue
#define HIGHWAY_CONSTRUCTION_COLOR Ceruleanblue
#define HIGHWAY_MINI_ROUNDABOUT_COLOR white
#define HIGHWAY_MOTORWAY_JUNCTION_COLOR Ceruleanblue
#define HIGHWAY_REST_AREA_COLOR Ceruleanblue
#define HIGHWAY_SERVICES_COLOR Ceruleanblue
#define HIGHWAY_TURNING_CICLE_COLOR white



#define HIGHWAY_MOTORWAY_SIZE 10.0f
#define HIGHWAY_TRUNK_SIZE 8.0f
#define HIGHWAY_PRIMARY_SIZE 5.0f
#define HIGHWAY_SECONDARY_SIZE 4.0f
#define HIGHWAY_TERTIARY_SIZE 3.0f
#define HIGHWAY_UNCLASSIFIED_SIZE 2.0f
#define HIGHWAY_RESIDENTIAL_SIZE 2.0f
#define HIGHWAY_SERVICE_SIZE 1.0f
#define HIGHWAY_MOTORWAY_LINK_SIZE 2.0f
#define HIGHWAY_TRUNK_LINK_SIZE 5.0f
#define HIGHWAY_SECONDARY_LINK_SIZE 4.0f
#define HIGHWAY_PRIMARY_LINK_SIZE 5.0f
#define HIGHWAY_TERTIARY_LINK_SIZE 3.0f
#define HIGHWAY_LIVING_STREET_SIZE 2.0f
#define HIGHWAY_PEDESTRIAN_SIZE 2.0f
#define HIGHWAY_TRACK_SIZE 0.3f
#define HIGHWAY_BUS_GUIDEWAY_SIZE 0.5f
#define HIGHWAY_RACEWAY_SIZE 1.0f
#define HIGHWAY_ROAD_SIZE 1.0f
#define HIGHWAY_FOOTWAY_SIZE 0.3f
#define HIGHWAY_BRIDLEWAY_SIZE 0.3f
#define HIGHWAY_STEPS_SIZE 0.7f
#define HIGHWAY_PATH_SIZE 0.3f
#define HIGHWAY_CYCLEWAY_SIZE 0.3f
#define HIGHWAY_PROPOSED_SIZE 1.0f
#define HIGHWAY_CONSTRUCTION_SIZE 1.0f
#define HIGHWAY_ROUNDABOUT_SIZE 1.0f
#define HIGHWAY_MOTORWAY_JUNCTION_SIZE 1.0f
#define HIGHWAY_REST_AREA_SIZE 0.5f
#define HIGHWAY_SERVICES_SIZE 0.5f
#define HIGHWAY_TURNING_CICLE_SIZE 1.0f



#define BUILDING BurnishedBrown
//#define LANDUSE glColor3f(0.8f,0.8f,0.8f)
#define AREA Ashgrey
#define WATERWAY Aero

#define NATURAL_WOOD_COLOR Budgreen
#define NATURAL_TREE_ROW_COLOR Budgreen
#define NATURAL_TREE_COLOR Budgreen
#define NATURAL_SCRUB_COLOR Darkseagreen
#define NATURAL_HEATH_COLOR Darkkhaki
#define NATURAL_GRASSLAND_COLOR Darkseagreen
#define NATURAL_FELL_COLOR Darkkhaki
#define NATURAL_BARE_ROCK_COLOR Darkmediumgray
#define NATURAL_SCREE_COLOR Champagnepink
#define NATURAL_SHINGLE_COLOR Champagnepink
#define NATURAL_SAND_COLOR Buff
#define NATURAL_MUD_COLOR Bazaar
#define NATURAL_WATER_COLOR Aero
#define NATURAL_WETLAND_COLOR Aero
#define NATURAL_GLACIER_COLOR Beaublue
#define NATURAL_BAY_COLOR Aero
#define NATURAL_BEACH_COLOR Arylideyellow
#define NATURAL_COASTLINE_COLOR Bone
#define NATURAL_SPRING_COLOR Aero
#define NATURAL_HOT_SPRING_COLOR Aero
#define NATURAL_GEYSER_COLOR Aero
#define NATURAL_LAND_COLOR Ashgrey

#define LANDUSE_ALLOTMENTS_COLOR Antiquebrass
#define LANDUSE_BASIN_COLOR Airsuperiorityblue
#define LANDUSE_BROWNFIELD_COLOR Artichoke
#define LANDUSE_CEMTERY_COLOR Budgreen
#define LANDUSE_COMMERCIAL_COLOR Bubblegum
#define LANDUSE_CONSTRUCTION_COLOR Darkseagreen
#define LANDUSE_FARMLAND_COLOR Artichoke
#define LANDUSE_FARMYARD_COLOR Apricot
#define LANDUSE_FOREST_COLOR BrownYellow
#define LANDUSE_GARAGES_COLOR Budgreen
#define LANDUSE_GRASS_COLOR Ashgrey
#define LANDUSE_GREENFIELD_COLOR Darkseagreen
#define LANDUSE_GREENHOUSE_HORTICULTURE_COLOR Antiflashwhite
#define LANDUSE_INDUSTRIAL_COLOR Deepchampagne
#define LANDUSE_LANDFILL_COLOR Brightube
#define LANDUSE_MEADOW_COLOR Artichoke
#define LANDUSE_MILITARY_COLOR Fuchsiapink
#define LANDUSE_ORCHARD_COLOR Budgreen
#define LANDUSE_QUARRY_COLOR DarkgrayX11
#define LANDUSE_RAILWWAY_COLOR Brightube
#define LANDUSE_RECREATION_GROUND_COLOR Darkseagreen
#define LANDUSE_RESERVOIR_COLOR Airsuperiorityblue
#define LANDUSE_RESIDENTIAL_COLOR Ashgrey
#define LANDUSE_RETAIL_COLOR Flamingopink
#define LANDUSE_VILLAGE_GREEN_COLOR Darkseagreen
#define LANDUSE_VINEYARD_COLOR Budgreen

#define LEISURE_ADULT_GAMING_CENTRE_COLOR Cyclamen
#define LEISURE_AMUSEMENT_ARCADE_COLOR Cyclamen
#define LEISURE_BEACH_RESORT_COLOR Cyancobaltblue
#define LEISURE_BANDSTAND_COLOR Darkcandyapplered
#define LEISURE_BIRD_HIDE_COLOR Darkchestnut
#define LEISURE_DANCE_COLOR Darkpink
#define LEISURE_DOG_PARK_COLOR Deepchampagne
#define LEISURE_FIREPIT_COLOR Deer
#define LEISURE_FISHING_COLOR Darkseagreen
#define LEISURE_GARDEN_COLOR Darkseagreen
#define LEISURE_GOLF_COURSE_COLOR Budgreen
#define LEISURE_HACKERSPACE_COLOR Deer
#define LEISURE_ICE_RINK_COLOR white
#define LEISURE_MARINA_COLOR Airsuperiorityblue
#define LEISURE_MINIATURE_GOLF_COLOR Budgreen
#define LEISURE_NATURE_RESERVE_COLOR Budgreen
#define LEISURE_PARK_COLOR Darkseagreen
#define LEISURE_PITCH_COLOR Deepgreencyanturquoise
#define LEISURE_PLAYGROUND_COLOR Darkseagreen
#define LEISURE_SLIPWAY_COLOR Airsuperiorityblue
#define LEISURE_SPORT_CENTRE_COLOR Emerald
#define LEISURE_STADIUM_COLOR Emerald
#define LEISURE_SUMMER_CAMP_COLOR Darkseagreen
#define LEISURE_SWIMMING_AREA_COLOR Airsuperiorityblue
#define LEISURE_SWIMMING_POOL_COLOR Airsuperiorityblue
#define LEISURE_TRACK_COLOR Darkseagreen
#define LEISURE_WATER_PARK_COLOR Airsuperiorityblue
#define LEISURE_WILDLIFE_HIDE_COLOR Englishred


extern int showFrame;
extern int projection;

void Display_Frame();
void Display_Render(SDL_Renderer* renderer, int width, int height, float dx, float dy, float zoom);

void Render_Border(way w);

void Render_Glist(GLuint i);

void Render_Default(way w);

void Render_Highway(way w);

void Render_Building(way w);

void color_landuse(int n);

void color_natural(int n);

void color_leisure(int n);



#endif
