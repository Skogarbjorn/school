var canvas;
var gl;

var numVertices  = 36;

var points = [];
var colors = [];

var movement = false;
var spinX = 0;
var spinY = 0;
var zoom = 1;
var origX;
var origY;

var tween = 0;

var matrixLoc;

var cubes = [];
var prevCubes = [];

window.onload = function init()
{
    canvas = document.getElementById( "gl-canvas" );

    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }

	initCubes();
    colorCube();

    gl.viewport( 0, 0, canvas.width, canvas.height );
    gl.clearColor( 0.9, 1.0, 1.0, 1.0 );

    gl.enable(gl.DEPTH_TEST);

    //
    //  Load shaders and initialize attribute buffers
    //
    var program = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.useProgram( program );

    var cBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, cBuffer );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(colors), gl.STATIC_DRAW );

    var vColor = gl.getAttribLocation( program, "vColor" );
    gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vColor );

    var vBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, vBuffer );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(points), gl.STATIC_DRAW );

    var vPosition = gl.getAttribLocation( program, "vPosition" );
    gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vPosition );

    matrixLoc = gl.getUniformLocation( program, "rotation" );

    canvas.addEventListener("mousedown", function(e){
        movement = true;
        origX = e.offsetX;
        origY = e.offsetY;
        e.preventDefault();
    } );

    canvas.addEventListener("mouseup", function(e){
        movement = false;
    } );

    canvas.addEventListener("mousemove", function(e){
        if(movement) {
    	    spinY = ( spinY + (origX - e.offsetX) ) % 360;
            spinX = ( spinX + (origY - e.offsetY) ) % 360;
            origX = e.offsetX;
            origY = e.offsetY;
        }
    } );

	canvas.addEventListener("wheel", function(e){
		zoom += e.deltaY * 0.001;
	});

	tick();

    render();
}

function updateCubes() {
	for (var i = 0; i < 10; i++) {
		for (var j = 0; j < 10; j++) {
			for (var k = 0; k < 10; k++) {
				prevCubes[i][j][k] = cubes[i][j][k];
			}
		}
	}
	for (var i = 0; i < 10; i++) {
		for (var j = 0; j < 10; j++) {
			for (var k = 0; k < 10; k++) {
				let sum = countSurrounding(i, j, k);
				let cube = prevCubes[i][j][k];
				if ((cube == 1 && (sum < 5 || 7 < sum)) || (cube == 0 && sum == 6 )) {
					cubes[i][j][k] = cube^1;
				}
			}
		}
	}
}

function countSurrounding(x, y, z) {
	var count = 0;
	for (var i = x-1; i <= x+1; i++) {
		for (var j = y-1; j <= y+1; j++) {
			for (var k = z-1; k <= z+1; k++) {
				let a = (i + 10) % 10;
				let b = (j + 10) % 10;
				let c = (k + 10) % 10;
				count += prevCubes[a][b][c];
			}
		}
	}
	return count > 0 ? count-prevCubes[x][y][z] : 0;
}

function colorCube()
{
    quad( 1, 0, 3, 2 );
    quad( 2, 3, 7, 6 );
    quad( 3, 0, 4, 7 );
    quad( 6, 5, 1, 2 );
    quad( 4, 5, 6, 7 );
    quad( 5, 4, 0, 1 );
}

function quad(a, b, c, d) 
{
    var vertices = [
        vec3( -0.5, -0.5,  0.5 ),
        vec3( -0.5,  0.5,  0.5 ),
        vec3(  0.5,  0.5,  0.5 ),
        vec3(  0.5, -0.5,  0.5 ),
        vec3( -0.5, -0.5, -0.5 ),
        vec3( -0.5,  0.5, -0.5 ),
        vec3(  0.5,  0.5, -0.5 ),
        vec3(  0.5, -0.5, -0.5 )
    ];

    var vertexColors = [
        [ 0.0, 0.0, 0.0, 1.0 ],  // black
        [ 1.0, 0.0, 0.0, 1.0 ],  // red
        [ 1.0, 1.0, 0.0, 1.0 ],  // yellow
        [ 0.0, 1.0, 0.0, 1.0 ],  // green
        [ 0.0, 0.0, 1.0, 1.0 ],  // blue
        [ 1.0, 0.0, 1.0, 1.0 ],  // magenta
        [ 0.0, 1.0, 1.0, 1.0 ],  // cyan
        [ 1.0, 1.0, 1.0, 1.0 ]   // white
    ];

    // We need to parition the quad into two triangles in order for
    // WebGL to be able to render it.  In this case, we create two
    // triangles from the quad indices
    
    //vertex color assigned by the index of the vertex
    
    var indices = [ a, b, c, a, c, d ];

    for ( var i = 0; i < indices.length; ++i ) {
        points.push( vertices[indices[i]] );
        colors.push(vertexColors[a]);
        
    }
}

function initCubes() {
	for (var i = 0; i < 10; i++) {
		cubes[i] = [];
		prevCubes[i] = [];
		for (var j = 0; j < 10; j++) {
			cubes[i][j] = [];
			prevCubes[i][j] = [];
			for (var k = 0; k < 10; k++) {
				if (Math.random() > 0.8) {
					cubes[i][j][k] = 1;
				} else {
					cubes[i][j][k]= 0;
				}
				prevCubes[i][j][k] = 0;
			}
		}
	}
}

function tick() {
	updateCubes();
	tween = 0;
	setTimeout(function() {
		tick();
	}, 2000);
}

function bounce_curve(x) {
	let c1 = 1.70158;
	let c3 = c1 + 1;
	return 1 + c3 * Math.pow(x - 1, 3) + c1 * Math.pow(x - 1, 2);
}

function exp_curve(x) {
	return x === 1 ? 1 : 1 - Math.pow(2, -10 * x);
}

function render()
{
    gl.clear( gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

	if (tween < 0.99) {
		tween += 0.01;
	}

	var s_in = bounce_curve(tween) * 0.9;
	var s_out = 0.9 - exp_curve(tween) * 0.9;

    var mv = mat4();
	mv = mult( mv, scalem(zoom, zoom, zoom) );
    mv = mult( mv, rotateX(spinX) );
    mv = mult( mv, rotateY(spinY) );
	
	mv = mult( mv, scalem( 0.1, 0.1, 0.1 ) );
	mv = mult( mv, translate( -5, -5, -5 ) );
	for ( var i = 0; i < 10; i++ ) {
		for ( var j = 0; j < 10; j++ ) {
			for ( var k = 0; k < 10; k++ ) {
				let mv1 = mult( mv, translate(i, j, k) );
				if ( cubes[i][j][k] == 1 ) {
					if ( cubes[i][j][k] != prevCubes[i][j][k] ) {
						mv1 = mult( mv1, scalem( s_in, s_in, s_in ) );
					} else {
						mv1 = mult( mv1, scalem( 0.9, 0.9, 0.9 ) );
					}
					gl.uniformMatrix4fv(matrixLoc, false, flatten(mv1));
					gl.drawArrays( gl.TRIANGLES, 0, numVertices );
				} else {
					if ( cubes[i][j][k] != prevCubes[i][j][k] ) {
						mv1 = mult( mv1, scalem( s_out, s_out, s_out ) );
						gl.uniformMatrix4fv(matrixLoc, false, flatten(mv1));
						gl.drawArrays( gl.TRIANGLES, 0, numVertices );
					}
				}
			}
		}
	}
    requestAnimFrame( render );
}

