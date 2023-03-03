#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MAX_POINTS 10
#define MAX_LEVELS 5

typedef struct point {
  int x, y;
} point;

//the quadtree structure has four pointers to child nodes (nw, ne, sw, and se- northwest, northeast, southwest, and southeast), 
//an array of point structures (points) to store the points contained within the region represented by the node, 
//an integer (num_points) to store the number of points in the array, 
//and four integers (x, y, width, and height) to store the coordinates and dimensions of the region represented by the node.

typedef struct quadtree {
  struct quadtree *nw, *ne, *sw, *se;
  point points[MAX_POINTS];
  //max_points = maximum number of points that can be stored in the points array for a single node
  int num_points;
  int x, y, width, height;
} quadtree;


quadtree *create_quadtree(int x, int y, int width, int height, int level) {
// Here we took an integer level, which represents the level of the quadtree in the recursive structure 
//(the root of the quadtree is at level 0, its children are at level 1, etc).
  quadtree *q = (quadtree*)malloc(sizeof(quadtree));//we first allocate memory for a new quadtree structure using malloc and assign the result to a quadtree pointer q
  q->nw = q->ne = q->sw = q->se = NULL;
  q->num_points = 0;
  //initializing the nw, ne, sw, and se pointers to NULL, and setting the num_points field to 0
  q->x = x;
  q->y = y;
  q->width = width;
  q->height = height;
  return q;
  //returning a pointer 'q' to the newly created and initialized quadtree structure
}

/* The insert_point function takes a pointer to the root node of the quadtree, a point structure representing the point to be inserted, 
and the current level of the quadtree as arguments. 
We return 1 if the point is successfully inserted into the quadtree, or 0 if it fails.

The function first checks if there is space in the current quadtree node or if the maximum level has been reached. 
If either of these conditions is true, the point is added to the current node and the function returns 1.

If the current node is full and the maximum level has not been reached, the current node is divided into four quadrants 
and the point is recursively inserted into the appropriate quadrant. The function continues this process until the point
is inserted into a leaf node or the maximum level is reached. */
int insert_point(quadtree *q, point p, int level) {

  if (q->num_points < MAX_POINTS || level == MAX_LEVELS) {
    // If there is space in the current quadtree node or we have reached
    // the maximum level, add the point to the current node and return.
    q->points[q->num_points++] = p;
    return 1;
  }

  // Otherwise, divide the current quadtree node into four quadrants and
  // recursively insert the point into the appropriate quadrant.
  if (q->nw == NULL) {
    int x = q->x;
    int y = q->y;
    int width = q->width / 2;
    int height = q->height / 2;
    q->nw = create_quadtree(x, y, width, height, level + 1);
    q->ne = create_quadtree(x + width, y, width, height, level + 1);
    q->sw = create_quadtree(x, y + height, width, height, level + 1);
    q->se = create_quadtree(x + width, y + height, width, height, level + 1);
  }

  if (p.x < q->x + q->width / 2) {
    if (p.y < q->y + q->height / 2) {
      insert_point(q->nw, p, level + 1);
    } 
    else {
      insert_point(q->sw, p, level + 1);
    }
    return 1;
  } 
  else {
    if (p.y < q->y + q->height / 2) {
      insert_point(q->ne, p, level + 1);
    } 
    else {
      insert_point(q->se, p, level + 1);
    }
    return 1;
  }

}

void print_quadtree(quadtree *q, int level) {
  if (q == NULL) return; // checking if tree is empty, then return null as nothing to print

  // Print the points in the current quadtree node
  for (int i = 0; i < q->num_points; i++) {
    printf("(%d, %d)\n", q->points[i].x, q->points[i].y);
  }

  // Recursively print the points in the child nodes
  print_quadtree(q->nw, level + 1); // print points in northwest quadrant
  print_quadtree(q->ne, level + 1); // print points in northeast quadrant
  print_quadtree(q->sw, level + 1); // print points in southwest quadrant
  print_quadtree(q->se, level + 1); // print points in southeast quadrant
}


void delete_node(quadtree *q, int x, int y) {
  // Check if the current node is the one we want to delete
  for (int i = 0; i < q->num_points; i++) {
    if (q->points[i].x == x && q->points[i].y == y) {
      // Shift all the points after the one we want to delete one position to the left
      for (int j = i; j < q->num_points - 1; j++) {
        q->points[j] = q->points[j+1];
      }
      q->num_points--; // Decrement the number of points in the current node
      return; // Return from the function, as we have deleted the node
    }
  }

  // If the node is not in the current quadtree, recursively search in the appropriate quadrant
  if (q->nw != NULL) {
    if (x < q->x + q->width / 2) { // Check if the point is in the left half of the quadtree
      if (y < q->y + q->height / 2) { // Check if the point is in the top left quadrant
        delete_node(q->nw, x, y); // Recursively search in the northwest quadrant
      } 
      else {
        delete_node(q->sw, x, y); // Recursively search in the southwest quadrant
      }
    } 
    else { // Point is in the right half of the quadtree
      if (y < q->y + q->height / 2) { // Check if the point is in the top right quadrant
        delete_node(q->ne, x, y); // Recursively search in the northeast quadrant
      } 
      else {
        delete_node(q->se, x, y); // Recursively search in the southeast quadrant
      }
    }
  }
}


// Search a quadtree for a point with the given x and y coordinates.
// Returns a pointer to the quadtree node containing the point, or NULL if the point is not found.
quadtree *search_quadtree(quadtree *q, int x, int y) {
  if (q == NULL) return NULL; // Return NULL if the quadtree is empty

  // checking if the point is within the dimensions of the quadtree node
  // If the point's x and y coordinates are within the dimensions of the quadtree node, return the node.
  if (x >= q->x && x < q->x + q->width && y >= q->y && y < q->y + q->height) {
    return q;
  }

  // Recursively search the appropriate quadrant.
  // If the point's x coordinate is less than the midpoint of the quadtree node's width, search the northwest or southwest quadrants.
  // If the point's x coordinate is greater than or equal to the midpoint of the quadtree node's width, search the northeast or southeast quadrants.
  if (x < q->x + q->width / 2) {
    // If the point's y coordinate is less than the midpoint of the quadtree node's height, search the northwest quadrant.
    // Otherwise, search the southwest quadrant.
    if (y < q->y + q->height / 2) {
      return search_quadtree(q->nw, x, y);
    } 
    else {
      return search_quadtree(q->sw, x, y);
    }
  } 
  else {
    // If the point's y coordinate is less than the midpoint of the quadtree node's height, search the northeast quadrant.
    // Otherwise, search the southeast quadrant.
    if (y < q->y + q->height / 2) {
      return search_quadtree(q->ne, x, y);
    } 
    else {
      return search_quadtree(q->se, x, y);
    }
  }
}


// Calculate the distance between two points using euclid's formula
double distance(point p1, point p2) {
  double dx = p1.x - p2.x;
  double dy = p1.y - p2.y;
  return sqrt(dx * dx + dy * dy);
}

// Find the nearest neighbor of a point in a quadtree
point nearest_neighbor(quadtree *q, point p) {
  if (q == NULL) {
    // Quadtree is empty, return an invalid point
    return (point) { -1, -1 };
  }

  point nearest = (point) { -1, -1 };
  double min_distance = INFINITY;

  // Check if the current quadtree node is a leaf node
  if (q->nw == NULL) {
    // Current node is a leaf node, so check each point in the points array
    for (int i = 0; i < q->num_points; i++) {
      point pt = q->points[i];
      double d = distance(p, pt);
      if (d < min_distance) {
        min_distance = d;
        nearest = pt;
      }
    }
  }
  else {
    // Current node is an internal node, so check each child node recursively
    point nw = nearest_neighbor(q->nw, p);
    point ne = nearest_neighbor(q->ne, p);
    point sw = nearest_neighbor(q->sw, p);
    point se = nearest_neighbor(q->se, p);

    // Find the closest point among the child nodes
    double d = distance(p, nw);
    if (d < min_distance) {
      min_distance = d;
      nearest = nw;
    }
    d = distance(p, ne);
    if (d < min_distance) {
      min_distance = d;
      nearest = ne;
    }
    d = distance(p, sw);
    if (d < min_distance) {
      min_distance = d;
      nearest = sw;
    }
    d = distance(p, se);
    if (d < min_distance) {
      min_distance = d;
      nearest = se;
    }
  }
  // Return the nearest point after comparing distances 
  return nearest;
}

// Recursive function to free the memory for a quadtree
void clear_quadtree(quadtree *q) {
  // If the current quadtree node is NULL, return
  if (q == NULL) return;

  // Recursively clear the child nodes
  clear_quadtree(q->nw);
  clear_quadtree(q->ne);
  clear_quadtree(q->sw);
  clear_quadtree(q->se);

  // Free the memory for the current quadtree node
  free(q);
}


int main(int argc, char* argv[]) {
  // Create a quadtree for the region (0, 0) to (100, 100) with some points
  struct quadtree *q = create_quadtree(0, 0, 100, 100, 0);
  insert_point(q, (point) { 50, 50 }, 0);
  insert_point(q, (point) { 10, 20 }, 0);
  insert_point(q, (point) { 60, 70 }, 0);

  // Print the current structure of the quadtree
  printf("The current structure of the quadtree is:\n"); 
  print_quadtree(q, 0);

  // Declare variables to store user input
  int option, x, y, z;
  quadtree *temp;

  // Give the user a menu of options to choose from
  while (1) { 
    printf("To search, enter 1\nTo insert, enter 2\nTo delete, enter 3\nTo print, enter 4\nTo find nearest neighbor, enter 5\nTo stop, enter 6: "); 
    scanf("%d", &option); 

    switch (option) {
      case 1: { // Search for a node in the quadtree, returning true if it lies within the dimensions of the quadtree
        printf("Enter the node to be searched: ");
        scanf("%d", &x);
        scanf("%d", &y);
        temp = search_quadtree(q, x, y); 
        // 2 cases:
        if (temp == NULL) printf("The node is absent from the quadtree.\n\n");
        else printf("The node is present.\n\n");
        break;
      }
      case 2: { // Insert a node into the quadtree
        printf("Enter the node to be inserted: ");
        scanf("%d", &x);
        scanf("%d", &y);
        printf("Enter the level at which the node should be inserted: ");
        scanf("%d", &z);
        point p = {x, y};
        insert_point(q, p, z);
        printf("\n");
        printf("Element successfully inserted.\n");
        break;
      }
      case 3: { // Delete a node from the quadtree
        printf("Enter the node you want to delete: ");
        scanf("%d", &x);
        scanf("%d", &y);

        if (search_quadtree(q, x, y) == NULL) { // Check if the node is present
          printf("Element not present.\n");
        } else { // If the node is present, delete it
          delete_node(q, x, y);
          printf("Element successfully deleted.\n");
        }
        break;
      }
      case 4:{//to print the current quadtree
          printf("The nodes of the quadtree according to the levels are:\n");
          print_quadtree(q, 0);
          
          break;
      }

      case 5:{
        // Find the nearest neighbor of a point
          printf("Enter the node you want to find the nearest neighbour of: ");
          scanf("%d",&x);
          scanf("%d",&y);
          point p = {x, y};
          point nearest = nearest_neighbor(q, p);

          // Print the coordinates of the nearest neighbor
          printf("Nearest neighbor: (%d, %d)\n", nearest.x, nearest.y);
          break;
      }

      case 6:{ //To stop the code and take no more inputs for options 
          return 0;
      }

      default:{ //incase of wrong input from user
          printf("Wrong Input. Retry.\n \n");
          break;
      }
    }
  }
  // Free the memory for the quadtree
  clear_quadtree(q);
  
  return 0;
} 