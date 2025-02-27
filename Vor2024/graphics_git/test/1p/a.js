var canvas;
var gl;
var vBuffer; // Declare vBuffer globally

var points = [];
var colors = [];

var movement = false;     // Do we rotate?
var spinX = 0;
var spinY = 0;
var origX;
var origY;
var zoom = 1.0; // Default zoom level
var tween = 0.0; // Tween value for cube scaling
var numVertices = 36;

var zDist = 0.0;

var pos = [0.0, 0.0, 0.0];
var lookMatrix = moveLook(0, spinY);

var key = 0;
var glalpha;
var alpha = 1.0;

var matrixLoc;
var cellStates = [];
var nextCellStates = [];

window.onload = function init(){
	dir = [0.0, 0.0, 0.0];
    canvas = document.getElementById( "gl-canvas" );

    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }

    gl.viewport( 0, 0, canvas.width, canvas.height );
    gl.clearColor( 1.0, 1.0, 1.0, 1.0 );
    gl.enable(gl.DEPTH_TEST);

    colorCube();

    var program = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.useProgram( program );


    // Initialize buffers (only once)
    initializeBuffers(program);

    // Mouse event listeners for rotation
    setupMouseControls();

    render();
}

function initializeBuffers(program) {
    glalpha = gl.getUniformLocation( program, "alpha" );
	gl.uniform1f(glalpha, alpha);

    var cBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, cBuffer );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(colors), gl.STATIC_DRAW );

    var vColor = gl.getAttribLocation( program, "vColor" );
    gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vColor );

    vBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, vBuffer );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(points), gl.STATIC_DRAW );

    var vPosition = gl.getAttribLocation( program, "vPosition" );
    gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vPosition );

    pLoc = gl.getUniformLocation( program, "projection" );
    proj = perspective( 50.0, 1.0, 1.0, 500.0 );
    gl.uniformMatrix4fv(pLoc, false, flatten(proj));

    matrixLoc = gl.getUniformLocation( program, "transform" );
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

function quad(a, b, c, d) {
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
    
    //vertex color assigned by the index of the vertex
    var indices = [ a, b, c, a, c, d ];
    
    for ( var i = 0; i < indices.length; ++i ) {
        points.push( vertices[indices[i]] );
        colors.push(vertexColors[a]);
        
    }
}

function setupMouseControls() {
    // Mouse event listeners for rotation
    canvas.addEventListener("mousedown", function(e){
        movement = true;
        origX = e.offsetX;
        origY = e.offsetY;
        e.preventDefault();
    });
    
    canvas.addEventListener("mouseup", function(e){
        movement = false;
    });
    
    canvas.addEventListener("mousemove", function(e){
        if (movement) {
            spinY = (spinY + (origX - e.offsetX)) % 360;
            spinX = (spinX + (origY - e.offsetY)) % 360;
            origX = e.offsetX;
            origY = e.offsetY;
			lookMatrix = moveLook(key, spinY);
			key = 0;
        }
    });
    
    canvas.addEventListener("wheel", function(e) {
        // Prevent the default scrolling behavior
        e.preventDefault();
        
        // Adjust zoom level based on scroll direction
        zoom *= (e.deltaY < 0) ? 1.1 : 0.9; // Zoom in or out
        zoom = Math.max(0.1, Math.min(zoom, 10)); // Limit zoom level
    });

	window.addEventListener("keydown", function(e) {
		key = e;
		lookMatrix = moveLook(e, spinY);
	});
}

function moveLook(key, theta) {
	if (key != 0) {
		switch(key.keyCode) {
			case 87:
				pos[2]+=0.1;
				zDist += 0.1;
				break;
			case 83:
				pos[2]-=0.1;
				zDist -= 0.1;
				break;
			case 68:
				pos[0]-=0.1;
				break;
			case 65:
				pos[0]+=0.1;
				break;
		}
	}
	return lookAt(
		vec3(pos[0], pos[1], pos[2]),
		add(vec3(pos[0], pos[1], pos[2]),
			vec3(Math.cos(theta * (2*Math.PI)/360), 0.0, Math.sin(theta * (2*Math.PI)/360))),
		vec3(0.0, 1.0, 0.0));
}

function render() {
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    var mv = mat4();
    var mv1 = mat4();
	mv = mult(mv, lookMatrix);

	//mv = mult(mv, scalem(0.1, 0.1, 0.1));
	gl.uniformMatrix4fv(matrixLoc, false, flatten(mv));
	gl.drawArrays( gl.TRIANGLES, 0, numVertices);

	mv = mult(mv, translate(1.0, 0.0, 3.0));
	gl.uniformMatrix4fv(matrixLoc, false, flatten(mv));
	gl.drawArrays( gl.TRIANGLES, 0, numVertices);

    requestAnimFrame(render); // Request the next frame
}

